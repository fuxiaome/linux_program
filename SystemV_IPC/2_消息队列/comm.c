#include"comm.h"
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/types.h>

int msg_create_and_get(int flag)
{
	key_t _key = ftok(_PATH_, _PROJ_ID);
	if(_key < 0){
		perror("ftok");
		return -1;
	}
	//if no , creat, else failed
	int msg_id = msgget(_key, flag);
	if(msg_id < 0){
		perror("msgget");
		return -2;
	}
	return msg_id;
}

int msg_create()
{
	int flag = IPC_CREAT | IPC_EXCL;
	return msg_create_and_get(flag);
}

int msg_get()
{
	int flag = IPC_CREAT;
	return msg_create_and_get(flag);
}

int msg_send()
{
	return 0;
}

int msg_recv()
{
	return 0;
}

int msg_destroy()
{
	return 0;
}