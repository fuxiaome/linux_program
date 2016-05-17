#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

static void usage()
{
	printf("./client [remote_ip] [remote_port]\n");
}

int main()
{
	if(argc != 3){
		usage();
		return 1;
	}
	char *ip = argv[1];
	short port = atoi(argv[2]);
	int conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(conn_fd < 0){
		perror("socket error");
		return 1;
	}
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remore.sin_port = htons(port)
	inet_aton(ip, &remote.sin_addr);
	
	//connect(int sockfd, sockaddr *addr, addr_size);
	int ret = connect(conn_fd, &remote, sizeof(remote));
	if(ret == -1){
		perror("connect");
		close(conn_fd);
		return 0;
	}
	printf("connect success...tcp link is build...\n");
	char buf[1024];
	while(1){
		memset(buf, 0, sizeof(buf));
		printf("Please Enter data:\n");
		fflush(stdout);
		gets(buf);
		//忽略大小写进行比较
		if( strncasecmp(buf, "quit", 4) == 0 ){
			close(conn_fd);
			break;
		}
		write(conn_fd, buf, strlen(buf));
		int sz = read(conn_fd, buf, sizeof(buf));
		if(sz > 0){
			buf[sz] = '\0';
			printf("echo data:%s\n", buf);
		}
	}
	return 0;
}