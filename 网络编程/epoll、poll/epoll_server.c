#inlcude<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/epoll.h>

#define EVENT_SIZE 64

static void usage(char *proc)
{
	printf("%s [ip] [port]", proc);
}

//创建监听句柄
static int start(const char *ip, short port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("sock");
		return -1;
	}
	
	int flag = 1;//预防TIME_WAIT状态无法进行监听
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	
	int ret = bind(sock, (struct sockaddr *)&local, sizeof(local));
	if(ret < 0){
		perror("bind");
		return -1;
	}
	
	if(listen(sock, 5) < 0){
		perror("listen");
		return -1;
	}
}

//if return 0 read success and write success
static int read_write_data(int fd)
{
	char buf[1024];
	int len = sizeof(buf)-1;
	
	ssize_t sz = recv(fd, buf, len, 0);
	if(sz == 0){
		return 0;
	}else if(sz > 0){//echo data
		buf[sz] = '\0';
		printf("%s\n", buf);
		sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length:%d\r\n\r\nhello world", 13);
		send(fd, buf, strlen(buf), 0);
	}
	return 0;
}

//set nonblock
static int set_nonblock(int new_sock)
{
	int old_option = fcntl(new_sock, F_GETFL);
	if(old_option < 0){
		perror("fcntl(get)");
		exit(1);
	}
	fcntl(new_sock, F_SETFL, old_option | O_NONBLOCK);
	return old_option;
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 1;
	}
	
	char *ip = argv[1];
	short port = (short)atoi(argv[2]);
	int listen_sock = start(ip, port);
	
	int epfd = epoll_create(256);
	if(epfd < 0){
		perror("epoll_create");
		exit(1);
	}
	
	//定义epoll的事件
	struct epoll_event _event;
	_event.events = EPOLLIN;
	
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &_event);
	if(ret < 0){
		perror("epoll_ctl(for listen_sock)");
		exit(1);
	}
	
	//定义就绪事件的event数组,用作epoll_wait的输出型参数
	struct epoll_event _ready_event[EVENT_SIZE];
	int _ready_event_size = EVENT_SIZE;
	int timeout = 3000;
	
	while(1){//accept
		int ret = epoll_wait(epfd, _ready_event, _ready_event_size, timeout);
		switch(ret){
			case 0://timeout
				perror("timeout");
				break;
			case -1://error
				perror("epoll_wait");
				break;
			default: //hava least one thing is ready
				{
					int i = 0;
					//在这里ret就绪事件个数
					for(; i<ret; ++i){
						int fd = _ready_event[i].data.fd;
						
						//first do listen sock
						if(fd == listen_scok && _ready_event[i].events & EPOLLIN){	
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int new_sock = accept(fd, (struct sockaddr *)&client, &len);
							
							if(new_sock < 0){
								perror("accept");
								continue;
							}
							
							set_nonblock(new_sock);
							
							//accept success
							event.events = EPOLLIN | EPOLLOUT | EPOLLET;
							if(epoll_ctl(epfd, EPOLL_CTL_ADD, new_sock, &_event) < 0){
								perror("epoll_ctl(for new_sock)");
								close(new_sock);
								continue;
							}
						}else if((_ready_event[i].events & EPOLLIN ) && 
								 (_ready_event[i].events & EPOLLIN) ){//other socket
							if(read_write_data(fd) == 0){//read success and client close
								epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
								close(fd);
							}
						}
					}
				}
				break;
		}
	}
	
	return 0;
}