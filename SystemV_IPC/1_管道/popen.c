#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define _CMD_ 'ls -l'
#define _SIZE_ 1024

int main()
{
    //�������ִ�н��д��ܵ� (�ڲ�������һ���ܵ������������ӽ��� )�����ùܵ���
    //�����ļ�ָ�뷵��
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
    //�رչܵ��ļ���������
    pclose(f_p );
    return 0;
}
