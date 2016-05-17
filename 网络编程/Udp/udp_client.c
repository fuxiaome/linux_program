#include<stdio.h>
#define IP "xx.xx.xx.xx"

int main()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == -1){
		perror("sock");
		return 1;
	}
	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.port = htons(8080);
	remote.sin_addr.s_addr = inet_addr(IP);
	
	char buf[1024];
	while(1){
		memset(buf, 0, sizeof(buf));
		printf("Please enter:\n");
		fflush(stdout);
		gets(buf);
		socklen_t len = sizeof(remote);
		sendto(sock, buf, sizeof(buf)-1, 0, (struct sockaddr *)&remote, sizeof	(remote));
		recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr *)&remote, &		len);
		printf("receive form server:%s\n",buf);
	}
	return 0;
}