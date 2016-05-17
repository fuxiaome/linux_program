#ifndef _COMM_
#define _COMM_
#include<stdio.h>

#define _PATH_ "tmp"
#define _PROJ_ID_ 0x8888

int msg_create();//server
int msg_get();//client
int msg_send();
int msg_recv();
int msg_destroy();

#endif