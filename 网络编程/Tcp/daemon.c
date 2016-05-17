#include<stdio.h>

int main()
{
	umask(0);
	pid_t fd = fork();
	
	if(fd < 0){
		perror("fork error");
		exit(0);
	}else if(fd >0){//father
		exit(1);
	}
	//child 
	signal(SIGCHLD, SIG_IGN);
	setsid();
	
	if(fork() > 0 ){
		exit(0);
	}
	chdir("/");
	close(0);
	close(1);
	close(2);
	return 0;
}