#include"comm.h"

int main()
{
	int shm_id = shm_get();
	char *addr = shm_attach(shm_id);
	int i = 0;
	char msg = 'A';
	for(;i<26; ++i){
		addr[i] = msg+i;
		sleep(1);//向共享内存中写入26个字符
	}
	addr[i] = '\0';
	shm_detach(addr);
	//客户端不用释放共享内存的空间
	return 0;
}