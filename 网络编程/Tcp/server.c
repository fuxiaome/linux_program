#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void recycle(int sig)
{
	pid_t id;
	while(0 < ( id = wait_pid(-1, NULL, WNOHANG) )){
		printf("wait child success, pid:%d",id);
	}
}

static void usage()
{
	printf("Usage:./server [ip] [port]\n");
}

void echo_data(int new_sock)
{
	while(1){//处理一个客户端的请求
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		//读取失败，返回-1，读取到文件末尾返回0
		ssize_t sz = read(new_sock, buf, sizeof(buf)-1);
		if(sz > 0){//read data and remote is exist...
			buf[sz] = '\0';
			write(new_sock, buf, strlen(buf));//将数据回写
			printf("%s\n", buf);
		}else if(0 == sz){//tcp link is down
			printf("client is close\n");
			close(new_sock);
			break;
		}else{//read failed
			break;
			//DO Nothing
		}
	}
}

//return value is sock_fd(>=0) success
//return =-1 -> failed
int start(char *ip, short port)
{
	//(domain, type, protocol)
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0){
		perror("socket");
		return -1;
	}
	
	//处理SIG_CHILD信号，防止僵尸进程
	signal(SIG_CHILD, recycle);
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	inet_aton(ip, &local.sin_addr);
	int ret = bind(sock_fd, (struct sockaddr)&local, sizeof(local));
	if(ret < 0){
		perror("bind");
		return -1;
	}
	// listen(int sockfd, int backlog);
	// backlog告诉内核该socket可以监听多少个连接请求
	int listend = listen(sock_fd, 5);
	if( listend < 0){
		perror("listen");
		return -1;
	}
	while(1){
		struct sockaddr_in remote;
		memset(&remote, 0, sizeof(remote));
		socklen_t len = sizeof(remote);
		//第三个参数为一个输入输出型参数
		//以后客户端与服务器端传送数据均使用remote这个socket
		//原来的sock_fd继续接收新的连接请求
		int new_sock = accept(sock_fd, (struct sockaddr)&remote, &len);
		if(new_sock > 0){
			pid_t id = fork();
			if(0 == id){//child process
				close(sock_fd);//子进程不关注监听Socket
				echo_data(new_sock);
				exit(0);
			}else{//father process
				close(new_sock);//父进程不关注传送Socket
			}
			/*
			*/
			
		}
	}
}

int main(int argc, char *argv[])
{
	printf("this is a server.\n");
	
	if( argc != 3){
		usage();
		return 1;
	}
	char *ip = argv[1];
	short port = atoi(argv[2]);//string -> int 
	int fd = start(ip, port);
	
	return 0;
}