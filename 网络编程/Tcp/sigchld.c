#include<stdio.h>
#include<signal.h>
#include<string.h>


void handler(int sig)
{
	printf("catch %d sig",sig);
	int status = 0;
	pid_t id;
	while((id = waitpid(-1, &status, WNOHANG)) > 0){
		printf("wait success, pid:%d\n", id);
		if(WIFEXITED(status)){
			printf("exit code:%d\n",WEXITSTATUS(status));
		}
	}
}

int main()
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	
	sigaction(SIGCHLD, &act, NULL);
	
	pid_t id = fork();
	if( id < 0){
		perror("fork error");
		return 1;
	}else if( id == 0){
		printf("i'm child\n");
	}else{
		printf("i'm father\n"):
		pause();
	}
}