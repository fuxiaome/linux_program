#include<stdio.h>
#include<pthread.h>

int count = 0;

void *thread1(void *arg)
{
	int i = 5000;
	while(i){
		int temp = count;
		printf("thread1 : %d\n",temp);
		count = temp + 1;
		--i;
	}
	return NULL;
}

void *thread2(void *arg)
{
	int i = 5000;
	while(i){
		int temp = count;
		printf("thread2 : %d\n",temp);
		count = temp + 1;
		--i;
	}
	return NULL;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	int ret1 = pthread_create(&tid1, NULL thread1, NULL);
	int ret2 = pthread_create(&tid2, NULL thread1, NULL);
	printf("res:%d\n",count);
	return 0;
}