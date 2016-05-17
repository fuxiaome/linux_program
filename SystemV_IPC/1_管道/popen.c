#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define _CMD_ 'ls -l'
#define _SIZE_ 1024

int main()
{
    //将命令的执行结果写入管道 (内部创建了一个管道，并创建了子进程 )，将该管道文
    //件的文件指针返回
    FILE *f_p = popen( _CMD_, "r");
    if(f_p == NULL){//fail
        perror ("popen");
        exit (1);
    }
    
    char buf[_SIZE_ ];
    memset(buf , '\0' , sizeof (buf));
    size_t s = fread (buf, 1 , sizeof (buf)- 1, f_p );
    buf[s ] = '\0' ;
    printf("%s\n" ,buf);
    //关闭管道文件的输入流
    pclose(f_p );
    return 0;
}
