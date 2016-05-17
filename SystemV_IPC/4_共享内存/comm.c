#include"comm.h"

//实现代码复用，该函数仅限本函数使用
static int shm_create_get(int flag)
{
	key_t _key = ftok(_PAH_, _PROJ_ID_);
	
	if(_key < 0){
		perror("ftok");
		return -1;
	}
	
	return shmget(_key, _SIZE_, flag);
}

int shm_create()
{
	return shm_create_get(IPC_CREAT | IPC_EXCL | 0600);//0600表示权限
}

int shm_get()
{
	return shm_create_get(IPC_CREAT)
}

void* shm_attach(int shmid)
{
	return shmat(shmid, NULL, 0);
}
int shm_detach(int shmid)
{
	sh
	return 0;
}
int shm_destroy(int shmid)
{
	return shmctl(shmid, IPC_RMID, NULL);
}
