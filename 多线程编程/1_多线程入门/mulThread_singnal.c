#include<stdio.h>
#include<signal.h>

void sig_handler(int signo)
{
	printf("i receive %d singnal!\n",signo);
	return;
}

int main()
{
	while(1){
		//收到信号后，将去执行指定的函数，此时相当于一个函数出现两个执行流
		signal(2, sig_handler);//为2号信号增加处理信号,第二个参数为函数指针
		printf("hahaha");
	}
	return 0;
}