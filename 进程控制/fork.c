#include<stdio.h>
#include<unistd.h> //fork()函数包含在该头文件中

int main()
{
    printf("Test buffer!" )
    pid_t pid = fork ();
    
    if(pid == -1)
    {
        printf ("Process create fail!");
    }else if(pid == 0){
        printf ("This is father process!");
    }else{
        printf ("This is childe process!");
    }

    return 0;
}
