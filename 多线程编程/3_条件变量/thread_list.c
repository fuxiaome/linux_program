#include"thread_list.h"

//用于创建一个新的节点
static node_ptr but_node(elem_type _data)
{
	node_ptr new_node = (node_ptr)malloc(sizeof(node));
	if(NULL != new_node){
		new_node->data = _data;
		new_node->next = NULL;
	}
	return new_node;
}

static void delete_node(node_ptr head)
{
	if(head != NULL){
		free(head);
	}
}
//初始化链表
void init_list(node_pptr head)
{
	if(NULL == (*head = buy_node(0)){
		exit(1);
	}else{
		*head->data = 0;
	}
}

int push_front(node_ptr head, elem_type data)
{
	int res = _FALSE_
	node_ptr tmp = buy_node(data);
	if(NULL != tmp){
		tmp->next = head->next;
		head->next = tmp;
		res = _TRUE_;
	}
	return res;
}

void pop_front(node_ptr head, elem_type *data)
{
	if(!head || !head->next){
		return _FALSE_;
	}
	node_ptr tmp = head->next;
	*data = temp->data;
	head->next = temp->next;
	tmp->next = NULL;
	delete_node(tmp);
}

void show_list(node_ptr head);
{
	if(!head){
		return;
	}
	node_ptr cur = head->next;
	while(cur){
		printf("%d ",cur->data);
		cur = cur->next;
	}
	printf("\n");
}

int is_empty(node_ptr head)
{
	return head && head->next == NULL ? _TRUE_:_FALSE_;
}