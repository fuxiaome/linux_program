#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wati.h>

int main()
{
    pid_t id = fork ();
    if(id < 0)
    {   
        perror ("fork fail");//进程创建失败
        exit (1);
    }else if(0 == id){//child
        printf ("this is child!\n");
        sleep (5);
    }else{//father
        printf ("this father ,id :%d, pid :%d\n",getpid (),getppid());
         //调用wait 函数后，父进程会等待子进程退出后才会退出，此种等待为阻塞式等待
         int status = 0;
         //pid_t ret = wati(NULL);//参数为NULL 仅释放子进程的相关信息，不关心其具体状态，避免其为僵尸进程
        pid_t ret = wati(& status);// 获得子进程的状态信息
         if(ret < 0 )
         {
            perror ("wait fail!\n");//调用wait 函数失败，输出错误信息
         }else{
            printf ("wait success！ wait pid is %d\n",ret );//调用成功返回子进程的 pid
            printf ("child get signal no:%d\n",0xff&status );//低八位，异常退出时的信号，信号非零表示异常退出
            printf ("child quit code:%d\n",0xff&(status >>8)); //次低八位, 退出码
            
         }
    }
    printf("this proc is quit pid:%d\n" ,getpid());
    exit(8 );
    return 0;
}
