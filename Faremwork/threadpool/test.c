#include "sql.h"
#include <stdio.h>
int main(void) {
    MYSQL *my = NULL;
    connection(&my, "root", "111111", "linux66");
    update(my, "insert into t1 values(10, 'abc')");
}
