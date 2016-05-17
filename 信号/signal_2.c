#include<stdio.h>
#include<string.h>
#include<signal.h>
//1、模拟实现sleep函数
//2、Linux信号
//3、负载均衡
//4、pause函数详解 SIG_DFL　SIG_IGN

void handler(int sig)
{
	printf("catch a signal ,number is:%d\n",sig);
}

int main()
{
	//signal(SIGINT, handler);
	struct sigaction new_action;
	struct sigaction old_action;
	memset(&new_action, 0, sizeof(new_action));
	new_action.sa_handler = handler;
	sigemptyset(&new_action.sa_mask);//初始化信号屏蔽字
	sigaction(SIGINT, &new_action，&old_action);
	while(1){
		printf("current in while.\n");
		sleep(1);
	}
	return 0;
}