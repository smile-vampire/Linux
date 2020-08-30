#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化链表
list_t *list_init() 
{
	list_t *p = (list_t*)malloc(sizeof(list_t));
	memset(p, 0x00, sizeof(list_t));

	p->head = NULL;
	p->len = 0;
}

// 往链表中插入数据
int list_insert(list_t *list, const char *key, const char *value)
{
	node_t *newnode = (node_t*)malloc(sizeof(node_t));

	memset(newnode, 0x00, sizeof(node_t));
	newnode->name = malloc(strlen(key)+1);
	strncpy(newnode->name, key, strlen(key));
	newnode->value = malloc(strlen(value)+1);
	strncpy(newnode->value, value, strlen(value));
	
	if ( list->head == NULL ) {
		list->head = newnode;
	} else {
		newnode->next = list->head;
		list->head = newnode;
	}
	list->len++;
}

