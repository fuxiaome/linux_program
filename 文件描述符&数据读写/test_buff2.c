#include<stdio.h>
const char * msg = "hahhal";
int main()
{
    printf("%s\n" , msg); //��ֱ������þ仰��û��ˢ�»�������printf����ʹ���˻������
    write(1 , msg , sizeof(msg ));//ֱ������þ仰��û�н��л���
    //ʹ�û�����Ч�ʸߣ�������ķ��ʴ�������
    fwrite();//Ч��ͬprintf���ú���ʹ���˻������
    sleep(4 );
    return 0;
}
