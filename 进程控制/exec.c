#include<stdio.h>
#include<unistd.h>

int main( int argc, char *argv[])
{
    //printf("%s\n",argv[0]);//��ʾ���������
    execl("/bin/ls" , "ls" , "-i" , NULL );//�滻 Main�����߳�
    return 0;
}
