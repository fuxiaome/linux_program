#include<stdio.h>
const char * msg = "hahhal";
int main()
{
    printf("%s\n" , msg); //不直接输出该句话，没有刷新缓冲区，printf函数使用了缓冲机制
    write(1 , msg , sizeof(msg ));//直接输出该句话，没有进行缓冲
    //使用缓冲区效率高，对外设的访问次数减少
    fwrite();//效果同printf，该函数使用了缓冲机制
    sleep(4 );
    return 0;
}
