#include<stdio.h>
#include<pthread.h>

int count = 0;
pthread_mutex_t _mutex;//定义全局的信号量，实现锁的机制

//初始化互斥锁
int lock_init(pthread_mutex_t *_lock)
{
	pthread_mutex_init(_lock, NULL);
}
//申请互斥锁操作
int lock(pthread_mutex_t *_lock)
{
	return pthread_mutex_lock(_lock);
}
//释放互斥锁操作
int unlock(pthread_mutex_t *_lock)
{
	pthread_mutex_unlock(_lock);
}
int lock_delete(pthread_mutex_t *_lock)
{
	return pthread_mutex_destroy(_lock);
}

void *thread1(void *arg)
{
	int i = 5000;
	while(i){
		lock(&_mutex);
		int temp = count;
		printf("thread1 : %d\n",temp);
		count = temp + 1;
		--i;
		unlock(&_mutex);
	}
	return NULL;
}

void *thread2(void *arg)
{
	int i = 5000;
	while(i){
		lock(&_mutex);
		int temp = count;
		printf("thread2 : %d\n",temp);
		count = temp + 1;
		--i;
		unlock(&_mutex);
	}
	return NULL;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	lock_init(&_mutex);//对信号量进行初始化
	int ret1 = pthread_create(&tid1, NULL thread1, NULL);
	int ret2 = pthread_create(&tid2, NULL thread1, NULL);
	printf("res:%d\n",count);
	return 0;
}