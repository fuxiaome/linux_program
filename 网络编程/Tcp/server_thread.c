#include<stdio.h>
#include<pthread.h>

static void *service(void *arg)
{
	//为了让子线程执行完毕后资源得到回收，使用线程分离
	//方法一：自己使自己分离
	pthread_detach(pthread_self());
	printf("thread create success and set it detach\n");
	int new_sock = (int)arg;
	echo_data(new_sock);
	
}

void server()
{
	pthread t_tid;
	pthread_create(&tid, NULL, service, (void *)new_sock);
	/*
		方法二：主进程设置分离
		pthread_detach(tid);
	*/
}