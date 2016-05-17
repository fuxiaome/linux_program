#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main( int argc, char *argv[])
{
    int fd[2 ];
    int ret = pipe (fd); //成功返回0
    if(ret < 0 )//failed
    {
        perror ("pipe");
        exit (1);
    }
//在编译选项上加入
#ifdef_DEBUG
    printf("pipe success,fd[0]:%d,fd[1]:%d\n" ,fd[ 0],fd [1]);
#endif
    pid_t id = fork ();
    if(id < 0){//fork error
        perror ("fork");
        close (fd[ 0]);
        close (fd[ 1]);
        exit (2);
    }else if(id == 0){//fork success,child
         //子进程进行读取,关闭写端
        close (fd[ 1]);
#define _SIZE_ 1024
         char buf[ _SIZE_];
        memset (buf, '\0' , sizeof (buf));
         int i = 10 ;
         while(i ){
             ssize_t s = read(fd [0], buf ,sizeof(buf)- 1);
             if(s > 0 ){
                buf [s] = '\0';
                printf ("child pid:%d,father said:%s\n", getpid(),getppid (),buf);
             }else if(s == 0 ){
                printf (writer stop writintg,close fd[1 ]\n);
                 break;
             }
            i --;
         }
    }else{//father
         //父进程进行写入，关闭读端
        close (fd[ 0]);// 以程序为参考区别输入输出
         char * msg = "haha lala!";
        printf ("father %d\n",getpid());
         int i = 10 ;
         while(i ){
            write (fd[ 1], msg , strlen(msg));// 不需要写'\0'
            sleep (1);
            i --;
         }   
        close (fd[ 1]);
         int ret = waitpid(id , NULL , 0 );
         if(ret == id){ //wait success
            printf ("wait success!\n");
         }else{
            perror ("waitpid");
            exit (3);
         }
    }
    return 0
}