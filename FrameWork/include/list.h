#ifndef __LIST_H__
#define __LIST_H__

typedef struct node {
	char *name;
	char *value;
	struct node *next;
}node_t;

typedef struct list {
	node_t *head;
	int len;
}list_t;

// 初始化链表
list_t *list_init(); 

// 往链表中插入数据
int list_insert(list_t *head, const char *key, const char *value);

#endif //__LIST_H__

