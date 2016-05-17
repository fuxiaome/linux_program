#include<semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_destroy(sem_t *sem);

#include"thread_list.h"

node_ptr head = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//利用宏创建一个互斥锁
pthread_cond_t cond = PTHREA_COND_INITALIZER;//创建一个条件变量

void *producter(void *arg)
{
	int data = 0;
	while(1){
		pthread_mutex_lock(&mutex);
		printf("product data,data is:%d\n",data);
		push_front(head, data++);
		pthread_mutex_unlock(&mutex);
		printf("produt is done,,,\n");
		pthread_cond_signal(&cond);//向条件变量发送成立信号
		sleep(1);
	}
}

void *consumer(void *arg)
{
	elem_type _data;
	while(1){
		pthread_mutex_lock(&mutex);
		while(is_empty(head)){//保证唤醒后，链表不为空
			//当条件满足时，唤醒任一个在mutex上等待的线程，立即释放锁
			ptintf("data is empty,wait cond ,,,\n");
			pthread_cond_wait(&cond, &mutex);
			//唤醒所有在mutex上等待的线程
			//pthread_cond_broadcast(&cond);
		}
		int ret = pop_front(head, &_data);
		if( ret == _TRUE_){
			printf("consume data: %d\n",_data);
		}else{
			printf("no data can be consumed!\n");
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main()
{
	init_list(&head);
	pthread_t tid1,tid2;
	pthread_create(&tid1, NULL, producter, NULL);
	pthread_create(&tid2, NULL, consumer, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_mutex_detroy(tid1);
	pthread_mutex_detroy(tid2);
	return 0;
}