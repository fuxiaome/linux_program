#include<stdio.h>
#include<pthread.h>

void * thread_run(void *arg)
{
	sleep(20);
	int count = 3;
	while(count){
		printf("thread run,thread_id:%d,pid:%d\n",pthread_self(),getpid());
		count--;
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thread_run, (void *)1);//第二个参数为线程状态
	if( ret != 0){
		printf("create thread errot:%s\n",strerror(ret));
		return 1;
	}
	sleep(50);//使用& 可使程序在后台运行，使用jobs可以后台运行的工作，bg查看所有后台工作
	void *status ;
	pthread_join(tid, &status);//status获取线程执行状态
	printf("main thread run,thread_id:%d,pid:%d\n",pthread_self(),getpid());
	return 0;
}
