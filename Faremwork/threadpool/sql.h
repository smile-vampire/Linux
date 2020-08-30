#ifndef __SQL_H__
#define __SQL_H__

#include <mysql/mysql.h>

int connection(MYSQL **my, char *name, char *passwd, char* db);

//插入删除
int update(MYSQL* my, char *sql);

MYSQL_RES *query(MYSQL* my, char *sql);

#endif
