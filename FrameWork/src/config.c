#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>
#include <list.h>

static list_t *head = NULL;

// 加载, 在程序启动时，就应该将所有的配置信息加载到内存
void load(const char *conf_name)
{
	if ( conf_name == NULL ) 
		return;
	
	FILE *fp = fopen(conf_name, "r");
	if ( fp == NULL )
		return;

	head = list_init();

	char linebuf[501];
	while ( !feof(fp) ) {
		memset(linebuf, 0x00, sizeof(linebuf));
		if ( fgets(linebuf, 500, fp) == NULL ) // 从配置文件中读取一行数据
			continue;
		if ( linebuf[0] == '\0' )
			continue;
		if ( linebuf[0]==' ' || linebuf[0] == '\n' || linebuf[0] == '\r' ||
						linebuf[0] == '#' || linebuf[0] == '\t' ) 
			continue;
lab:
		if ( linebuf[strlen(linebuf)-1] == 10 || 
					linebuf[strlen(linebuf)-1] == 13 ||
					linebuf[strlen(linebuf)-1] == 32 ) {
			linebuf[strlen(linebuf)-1] = '\0';
			goto lab;
		}
		
		if ( linebuf[0] == '\0' || linebuf[0] == '[' ) 
			continue;

		// key = value
		char *ptmp = strchr(linebuf, '=');
		if ( ptmp != NULL ) {
			char name[500] = {};
			char value[500] = {};
			strncpy(name, linebuf, (int)(ptmp-linebuf));
			strcpy(value, ptmp+1);
			
			ltrim(name);
			rtrim(name);
			ltrim(value);
			rtrim(value);
			list_insert(head, name, value);
		}
	}

	fclose(fp);
}

// 读取字符串类型的配置项
const char *get_string(const char *key)
{
	node_t *tmp = head->head;
	while ( tmp != NULL ) {
		if ( strcmp(tmp->name, key) == 0 ) {
			return tmp->value;
		}
		tmp = tmp->next;
	}

	return NULL;
}

// 读取整数类型的配置项
int get_int_default(const char *key, const int def)
{
	int ret = def;

	node_t *tmp = head->head;
	while ( tmp != NULL ) {
		if ( strcmp(tmp->name, key) == 0 ) {
			ret = atoi(tmp->value);
			break;
		}
		tmp = tmp->next;	
	}

	return ret;
}

