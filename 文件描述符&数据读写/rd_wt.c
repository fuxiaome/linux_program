#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

#define _DEBUG

const char *msg = "change world\n";

int main()
{
    int fd = open ("./log",O_RDWR|O_CREAT , 0755 );
    if(fd < 0){
        perror ("open");
        exit (1);
    }
#ifdef _DEBUG
    printf("fd:%d\n" , fd);
#endif

    int i = 100;
    while(i){
        i --;
        write (fd, msg, sizeof(msg ));//将 msg写入文件中
    }
    
    char buf[64 ];
    memset(buf , '\0' , sizeof (buf));
    
    ssize_t ret ;
    do{
        ret = read( fd, buf, sizeof(buf )-1);
        buf [ret] = '\0'; //在字符串结尾加上结束标记，不加会出现乱码
        printf ("%s\n",buf);
    }while(ret > 0 );
    fflush(stdout );
    return 0;
}
