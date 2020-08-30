#ifndef __NET_CONNECTION_H__
#define __NET_CONNECTION_H__

typedef struct connection {
    int fd;
    int events; //当前状态，EPOLLIN还是EPOLLOUT
    void (*rdhandler)(struct connection *c);//读回调函数
    void (*wrhandler)(struct connection *c);//写回调函数
    char buffer[2000];//缓冲区
    struct connection *data; //相当于链表next指针
}connection_t;


int listen_init();//初始化侦听套接字

int epoll_init();

void epoll_process();//获取发生事件

#endif
