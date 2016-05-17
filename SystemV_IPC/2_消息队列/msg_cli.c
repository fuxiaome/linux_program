#include"comm.h"
int _msg_id = -1;

int msg_client_start()
{
	key_t _key = ftok(FILEPATH,ID);//创建键值
	if( _key < 0 ){
		printf("client get key id error");
		return 1;
	}
	msginfo _cli_info;
	msg_id = msgget(_key, 0); //获取信号队列ID
	
	if( _msg_id < 0 ){
		printf("msg_server get key id failed\n");
		return 1;
	}
	
	while(1){
		printf("client :>");
		fgets(_cli_info.mtext, sizeof(_cli_info.mtext),stdin);
		if(strncasecmp(_cli_info.mtext, "quit", 4) == 0){
			printf("client bye!\n");
			break;
		}
		_cli_info.mtype = g_cli_send_type;
		if( msgsnd(_msg_id, &_cli_info, __MSG_SIZE__, 0) == -1 ){
			printf("client send msg error\n");
			exit(0);
		}
		memset(_cli_info.mtext, '\0', sizeof(_cli_info.mtext));
		
		if( msgrcv(_msg_id, &_cli_info, __MSG_SIZE__, g_ser_send_type, 0) == -1 ){
			print_log("client recive msg error");
			return 1;
		}
	
		printf("server :>%s\n",_cli_info.mtext); 
	}
	return 0;
}

int msg_client_end(int id)
{
	if(msgctl(id, IPC_RMID, NULL) == -1){
		return 1;
	}
	return 0;
}

static void delete_msg(void)//删除消息队列
{
	if( _msg_id != -1 ){
		msg_client_end(_msg_id);
	}
	printf("delete msg queue end\n");
}

int main(int argc, char *argv[])
{
	if(msg_client_start() == 0){
		print_log("msg_server start success\n");
	}else{
		print_log("msg_server start failed\n");
	}
	return 0;
}