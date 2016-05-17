#include<stdio.h>
#include<pthread.h>

void *thread_run(void *arg)
{
	pthread_detach(pthread_self());//子线程将自己设置为分离状态
	printf("thread run!\n");
	sleep(10);
}

int main()
{
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thread_run, NULL);
	sleep(5);
	printf("main thread run\n");
	pthread_detach(tid);//将子线程设为分离状态
	printf("main set detach done...\n");
	sleep(2);
	//printf("main begin cancel\n");
	//pthread_cancel(tid); 取消子线程，该句可以正常完成
	//printf("main begin join\n");
	//int ret = pthread_join(tid, NULL); 主线程等待子线程，该句无法正常完成
	if(ret != 0){
		printf("%d : %s \n",ret, strerror(ret));//显示无效的参数的错误
		return 1;
	}
	return 0;
}