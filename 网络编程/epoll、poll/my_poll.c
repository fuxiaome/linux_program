#include<stdio.h>
#include<string.h>
#include<poll.h>

int main()
{
	struct pollfd fd_poll[1];
	fd_poll[0].fd = 0;//监听标准输入
	fd_poll[0].events = POLLIN;
	fd_poll[0].revents = 0;//该变量表示发生的事件，由内核填充
	
	int timeout = 3000;
	
	char buf[1024] = {0};
	while(1){
		memset(buf, 0, sizeof(buf));
		int ret = poll(fd_poll, 1, timeout);
		switch(ret){
			case 0:
				perror("timeout");
				break;
			case -1:
				perror("poll");
				break;
			default :
				if(fd_poll[0].revents | POLLIN ){
					gets(buf);
					printf("%s\n", buf);
					fd_poll[0].revents = 0;//进行下次监听前清空该变量
				}
				break;
		}
	}
	
	return 0;
}