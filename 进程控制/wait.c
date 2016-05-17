#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wati.h>

int main()
{
    pid_t id = fork ();
    if(id < 0)
    {   
        perror ("fork fail");//���̴���ʧ��
        exit (1);
    }else if(0 == id){//child
        printf ("this is child!\n");
        sleep (5);
    }else{//father
        printf ("this father ,id :%d, pid :%d\n",getpid (),getppid());
         //����wait �����󣬸����̻�ȴ��ӽ����˳���Ż��˳������ֵȴ�Ϊ����ʽ�ȴ�
         int status = 0;
         //pid_t ret = wati(NULL);//����ΪNULL ���ͷ��ӽ��̵������Ϣ�������������״̬��������Ϊ��ʬ����
        pid_t ret = wati(& status);// ����ӽ��̵�״̬��Ϣ
         if(ret < 0 )
         {
            perror ("wait fail!\n");//����wait ����ʧ�ܣ����������Ϣ
         }else{
            printf ("wait success�� wait pid is %d\n",ret );//���óɹ������ӽ��̵� pid
            printf ("child get signal no:%d\n",0xff&status );//�Ͱ�λ���쳣�˳�ʱ���źţ��źŷ����ʾ�쳣�˳�
            printf ("child quit code:%d\n",0xff&(status >>8)); //�εͰ�λ, �˳���
            
         }
    }
    printf("this proc is quit pid:%d\n" ,getpid());
    exit(8 );
    return 0;
}
