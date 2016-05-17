#include<stdio.h>
#include<string.h>
#include<unistd.h>

void alarm_handler(int sig)
{
	
}

int mysleep(int second)
{
	struct sigaction act, oact;
	memset(&act, 0, sizeof(act));//养成初始化的习惯，有可能出现段错误
	memset(&oact, 0, sizeof(oact));
	act.sa_handler = alarm_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, &oact);
	alarm(second);
	pause();
	int ret = alarm(0);//取消闹钟，返回值代表定时剩余时间
	sigaction(SIGALRM, &oact, NULL);
	return ret;
}

int main()
{
	return 0;
}