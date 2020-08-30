#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "net_connection.h"

int main(void) {
    listen_init();
    epoll_init();
    epoll_process();
}
