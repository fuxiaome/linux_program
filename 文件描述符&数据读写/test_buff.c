#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd = open ("./log",O_CREAT|O_RDWR ,0666);
    
    if(fd < 0)
    {
        perroe ("open");
        exit (1);
    }
    wirte(fd , "haha" , sizeof ("haha"));
    close(fd );
    return 0;
}
