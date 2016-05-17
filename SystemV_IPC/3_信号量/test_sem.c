#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"sem_lock.h"

int main()
{
	//未使用信号量时此时父子进程打印语句没有规律
	pid_t id = fork();
	int sem_id = sem_create(1);
	sem_init(sem_id, 0, 1);//对信号量集的一号信号量初始化为1
	if( id < 0 ){//faild
		perror("fork");
		exit(1);
	}else if(id == 0){//child
		int sem_id_child = sem_get(1);//获取父进程创建的信号量集
		while(1){
			sem_p(sem_id_child, 0);//对信号量集中的一号信号量执行P操作（0下标）
			printf("C");
			sleep(1);
			printf("C");
			sleep(3);
			fflush(stdout);//必须加上刷空语句，因为Printf没有\n
			sem_v(sem_id_child, 0);//对信号量集中的一号信号量执行V操作（0下标）
		}
		exit(1);
	}else{//father
		while(1){
			sem_p(sem_id, 0);//对信号量集中的一号信号量执行P操作（0下标）
			printf("F");
			sleep(2);
			printf("F");
			sleep(1);
			fflush(stdout);//必须加上刷空语句，因为Printf没有\n
			sem_v(sem_id, 0);//对信号量集中的一号信号量执行V操作（0下标）
		}
		wait(NULL);
		sem_destroy(sem_id);
	}
	return 0;
}