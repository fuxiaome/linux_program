#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#define _PATH_ "/ipc/mypipe.tmp"
#define _SIZE_ 256

//从管道读数据的进程
int main()
{
    int fd = open (_PATH, O_RDONLY);
    if(fd < 0){
        perror ("open");
        exit (2);
    }
    char buf[_SIZE_ ];
    while(1){
        memset (buf, '\0' , sizeof (buf));
         ssize_t s = read(fd , buf, sizeof(buf)- 1);
         if(s == 0 ){
            printf ("reader quit!\n");
         }else if(s > 0 ){
            buf [s] = '\0';
            printf ("reader:%s\n",buf);
         }else{
            perror ("read");
            exit (2);
         }
        
    }
    close(fd );

    return 0;
}
