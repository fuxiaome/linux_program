#include<stdio.h>
#include<pthread.h>

void * thread_run(void *arg)
{
	printf("%d\n",(int)*arg);
	while(1){
		printf("this thread! pid:%d,threadpid:%d\n",getpid(),pthread_self());
	}
	pthread_exit((void *)2);//退出当前线程
}

int main()
{
	pthread_t tid ;
	int ret = pthread_create(&tid, NULL, thread_run, (void *)1);
	printf("new thread:%u\n",tid);//只在当前进程中保持唯一
	while(1){
		printf("main thread! pid:%d\n,threadpid:%d",getpid(),pthread_self());
	}
	return 0;
}