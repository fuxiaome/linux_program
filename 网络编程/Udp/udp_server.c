#inlcude<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

static void usage(const char *msg)
{
	if(NULL != msg){
		printf("%s [ip] [port]\n",msg);
	}
}

//根据ip和port获得一个socket
//失败返回-1，成功返回套接字fd
int start(const char *ip, short port)
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);//SOCK_DGRAM表示UDP服务
	if(sock == -1){
		perror("socket");
		return -1;
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	//inet_ton(ip, &local.sin_addr);
	if( bind(sock, (struct sockaddr *)&local, sizeof(local)) == -1){
		perror("bind");
		return -1;
	}
	return sock;
	
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return 1;
	}
	const char *ip = argv[1];
	short port = atoi(argv[2]);//get prot
	int sock = start(ip, port);//start udp socket
	
	char buf[1024];
	
	if(sock > 0){
		while(1){
			memset(buf, 0, sizeof(buf));
			struct sockaddr_in client;
			socklen_t len = 0;
			int sz = recvform(sock, buf, sizeof(buf)-1, 0, (struct sockaddr 	*)&client, &len);
			printf("%s\n", buf);
			sendto(sock, buf, sizeof(buf)-1, 0, (struct sockaddr *)&client, 		len);
			
		}
		
	}
	
	return 0;
}