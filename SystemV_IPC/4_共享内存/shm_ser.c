#include"comm.h"

int main()
{
	int shm_id = shm_create();
	sleep(10);
	char *addr = shm_attach(shm_id);//进行内存的关联
	//服务器端不断从共享内存区中读取内容
	while(1){
		printf("%s\n",addr);
	}
	shm_detach(addr);//取消关联
	sleep(5);
	shm_destroy(shm_id);
	return 0;
}