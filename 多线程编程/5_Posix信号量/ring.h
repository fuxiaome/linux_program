#ifndef _RING_
#define _RING_

#include<stdio.h>
#define _SIZE_ 1024

typedef int elem_type;
const int _TRUE_ = 1;
const int _FALSE_ = 0;

typedef struct _ring{
	elem_type ring_buf[_SIZE_];
	int prev;//ringbuff的最前的位置
	int curr;//当前指向的位置
	int count;//当前缓存中数据的个数
}ring_t, *ring_ptr;

typedef enum{
	_FALAE_ = 0,
	_TRUE_,
	_UNKNOW_
}ret_t;

int put_data(elem_type _data);
int get_data(elem_type *_data_p);
void init_ring(ring_ptr _r);

#endif