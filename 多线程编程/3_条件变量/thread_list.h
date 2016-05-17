#ifndef _LIST_
#define _LIST_

#include<stdio.h>
#include<pthread.h>

typedef int elem_type;
typedef struct _node{
	elem_type data;
	struct _node *next;
}node_t, *node_ptr, **node_pptr;

void init_list();
void push_front(elem_type data);
void pop_front(node_ptr head, elem_type *data);
void show_list();
int is_empty(node_ptr head);

#endif