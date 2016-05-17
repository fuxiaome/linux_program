#include<stdlio.h>
#include<semaphore.h>
#include<pthread.h>
#include"ring.h"

sem_t product_blank_count;//空闲格子的信号量
sem_t consum_data_count;//可用数据的信号量
ring_t ring_buffer;

void *producter(void *arg)
{
	int data = 0;
	while(1){
		sem_wait(&product_blank_count);//申请一个空格
		put_data(&ring_buffer, data);//生产者不断向Buffer中存放数据
		sem_post(&consum_data_count);//释放一份资源
		sleep(1);
		data++;
	}
}

void *consumer(void *arg)
{
	int tmp = 0;
	while(1){
		sem_wait(&consum_data_count);//申请一份资源
		get_data(&ring_buffer, &tmp);
		sem_post(&product_blank_count);//释放一个空格子
		printf("consumer data is:%d\n", tmp);
	}
}

int main()
{
	sem_init(&product_blank_count, 0, _SIZE_);
	sem_init(&consum_data_count, 0, 0);
	
	init_ring(&ring_buffer);
	pthread_t id1, id2;
	pthread_create(&id1, NULL, producter, NULL);//第四个参数用来给执行多线程的函数传参
	pthread_create(&id1, NULL, producter, NULL);
	
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	
	sem_destroy(&consum_data_count);
	sem_destroy(&product_blank_count);
	return 0;
}