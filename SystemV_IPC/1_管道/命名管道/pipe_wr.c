#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#define _PATH_ "/ipc/mypipe.tmp"

//向管道写数据的进程
int main()
{
    char *msg = "haha lala" ;
    umask(0 );
    if(mkfifo(_PATH_ , S_IFIO | 0666) == 0){
         int fd = open(_PATH , O_WRONLY);
         if(fd < 0 ){
            perror ("open");
            exit (2);
         }
         int count = 10;
         while(count --){
            write (fd, msg, strlen (msg));
            sleep (1);
         }
        close (fd);
    }else{//fail
        perror ("mkfifo");
        exit (1);
    }
    return 0;
}
