#include "sql.h"
#include <stdio.h>

int connection(MYSQL **my, char *name, char *passwd, char* db) {
    *my = mysql_init(NULL);
    mysql_real_connect(*my, "localhost", name, passwd, db, 0, NULL, 0);
}

//插入删除
int update(MYSQL* my, char *sql) {
    mysql_query(my, sql);
}

//查询
MYSQL_RES *query(MYSQL* my, char *sql) {
    mysql_query(my, sql);
    return mysql_store_result(my);
}

