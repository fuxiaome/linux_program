#include<stdio.h>
#include<unistd.h>

int main( int argc, char *argv[])
{
    //printf("%s\n",argv[0]);//表示程序的名称
    execl("/bin/ls" , "ls" , "-i" , NULL );//替换 Main所在线程
    return 0;
}
