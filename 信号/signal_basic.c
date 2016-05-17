#include<srdio.h>
#include<sys/types.h>
#include<signal.h>

void show_pending(sigset_t *pending)
{
	if( NULL == pending){
		return;
	}
	int i =1 ;
	for(; i<32; ++i){
		if(sigismember(pending, i)){//this signal is exist pending set
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
}

int main()
{
	sigset_t newSet;
	sigset_t oldSet;
	sigset_t pendingSet;
	sigempty(&newSet);//init newSet
	sigempty(&oldSet);
	//block SIGINT
	sigaddset(&newSet, SIGINT);
	sigprocmask(SIG_SETMASK, &newSet, &oldSet);//mask SIGINT
	while(1){
		sigempty(&pendingSet);
		sigpending(&pendingSet);
		show_pending(&pendingSet);
		sleep(1);
	}
	return 0;
}

