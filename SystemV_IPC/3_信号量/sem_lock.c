#include"sem_lock.h"

int sem_create_get(int nsems, int flags)
{
	key_t _key = ftok(_PATH_, _PROJ_ID_);
	if(_key < 0){
		perror("ftok");
		return -1;
	}

	return semget(_key, nsems, flags);
}

//创建一个新的信号量
int sem_create(int nsems)
{
	return sem_create_get(nsems,IPC_CREAT | IPC_EXCL);
}

//获取一个已经存在的信号量
int sem_get(int nsems)
{
	return sem_create_get(nsems, IPC_EXCL);
}

int sem_init(int sem_id, int sem, int val)
{
	semun_t semval;
	semval.val = val;
	return semctl(sem_id, sem, SETVAL, &semval);
}

//实现PV操作的函数复用，仅限本文件使用
static int my_sem_op(int sem_id, int sem, int op)
{
	struct sembuf _op;
	_op.sem_num = sem;
	_op.sem_op = op;//传-1表示传进去后会加上该值
	_op.sem_flg = 0;//SEM_UNDO  避免P操作完后未执行V操作改程序崩溃
	return semop(sem_id, &_op, 1);//1表示
}
int sem_p(int sem_id, int sem)
{
	return my_sem_op(sem_id, sem, -1);
}

int sem_v()
{
	return my_sem_op(sem_id, sem, 1);
}

//将整个信号量集都删除
int sem_destroy(int sem_id)
{
	return semctl(sem_id, 0, IPC_RMID;
	return 0;
}

#ifdef _DEBUG__

int main()
{	
	int nsems = 1;
	int sem_id = sem_create(nsems);
	sleep(3);
	sem_init(sem_id, 0, 1);//将信号量集中第一个信号量值设置为1
	sem_p(sem_id, 0);//申请临界区资源
	sleep(1);
	sem_v(sem_id, 0);//释放临界区资源
	sem_destroy(sem_id);
	return 0;
}

#endif