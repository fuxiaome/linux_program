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
        write (fd, msg, sizeof(msg ));//�� msgд���ļ���
    }
    
    char buf[64 ];
    memset(buf , '\0' , sizeof (buf));
    
    ssize_t ret ;
    do{
        ret = read( fd, buf, sizeof(buf )-1);
        buf [ret] = '\0'; //���ַ�����β���Ͻ�����ǣ����ӻ��������
        printf ("%s\n",buf);
    }while(ret > 0 );
    fflush(stdout );
    return 0;
}
