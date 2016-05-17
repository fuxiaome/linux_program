#ifndef _COMM_SHM_
#define _COMM_SHM_

#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>

#define _SIZE_ 4096
#define _PATH ./
#define _PROJ_ID 0x6666

int shm_create();
int shm_get();
int shm_attach();
int shm_detach();
int shm_destroy(int shmid);

#endif