#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include "net_connection.h"
#include "threadpool.h"


#define CONNSIZE 1024
int lfd = 0;//监听套接字
int epfd = 0; //epoll操作句柄
threadpool_t  pool;
connection_t connections[CONNSIZE];//连接池
connection_t *free_connection = NULL; //连接池中空闲节点的头
struct epoll_event evts[CONNSIZE];//epoll_wait就绪事件数组

void event_accept(connection_t *oc);
void wait_request_handler(connection_t *oc);
void write_request_handler(connection_t *oc); 
void epoll_add_event(int fd, int rdevent, int wrevent, int entype, connection_t *c);

int listen_init() {
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    int op = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9898);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if(r == -1) 
        perror("bind"),exit(1);
    listen(lfd, SOMAXCONN);
}

//从连接池获取一个空闲连接
connection_t *get_connection(int fd) {
    connection_t *c = free_connection;
    free_connection = c->data;
    c->fd = fd;
    return c;
}

//关闭一个连接
void close_connection(connection_t *c) {
    close(c->fd);
    c->fd = -1;
    c->data = free_connection;
    free_connection = c;
}

int epoll_init() {
    epfd = epoll_create1(EPOLL_CLOEXEC);//新的进程加载进来原本的文件描述符关闭
    threadpool_init(&pool, 2);//线程池个数
    int i = CONNSIZE;
    connection_t *c = connections;
    connection_t *next = NULL;
    do {
        i--;
        c[i].data = next;
        c[i].fd = -1;
        next = &c[i];
    }while(i);
    free_connection = next;
    c = get_connection(lfd);//给监听套接字分配连接池节点
    c->rdhandler = event_accept;//监听套接字对应回调函数
    epoll_add_event(c->fd, 1, 0, EPOLL_CTL_ADD, c);//描述符，读，写
}

void event_accept(connection_t *oc) {
    int newfd = accept(oc->fd, NULL, NULL);
    connection_t *nc = get_connection(newfd);//接收客户端到来，分配连接池
    nc->rdhandler = wait_request_handler; //读回调函数
    nc->wrhandler = write_request_handler; //写回掉函数
    epoll_add_event(nc->fd, 1, 0, EPOLL_CTL_ADD, nc);//描述符，读，写
}

void epoll_add_event(int fd, int rdevent, int wrevent, int evtype, connection_t *c) {
    struct epoll_event ev;
    if(evtype == EPOLL_CTL_MOD) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
        ev.data.ptr = c;
        ev.events = c->events;
        if(c->events == EPOLLIN) {
            ev.events = EPOLLOUT;
            c->events = EPOLLOUT;
        }else if(c->events == EPOLLOUT) {
            ev.events = EPOLLIN;
            c->events = EPOLLIN;
        }
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    }else {
        if(rdevent == 1) {
            ev.events = EPOLLIN;
            c->events = EPOLLIN;
        }else if(wrevent == 1) {
            ev.events = EPOLLOUT;
            c->events = EPOLLOUT;
        }
        ev.data.ptr = c;
        epoll_ctl(epfd, evtype, fd, &ev);
    }
}

void *run(void *arg) {
    connection_t *c = (connection_t*)arg;
    //业务处理
    int i;
    for(i = 0; c->buffer[i]; i++) {
        if(c->buffer[i] >= 'a' && c->buffer[i] <= 'z') {
            c->buffer[i] -= 32;
        }
    }
    epoll_add_event(epfd, 0, 0, EPOLL_CTL_MOD, c);
}

void wait_request_handler(connection_t *c) {
    int r = read(c->fd, c->buffer, 2000);
    if(r <= 0) {
        epoll_ctl(epfd, EPOLL_CTL_DEL, c->fd, 0); //对方关闭，从红黑树删除
        close_connection(c);//归还连接池
    }
    //将任务放入到线程池处理
    threadpool_add_task(&pool, run, c);
}
void write_request_handler(connection_t *c) {
    write(c->fd, c->buffer, strlen(c->buffer));
    //发送完毕之后，就直接转为监控epollin事件
    epoll_add_event(c->fd, 0, 0, EPOLL_CTL_MOD, c);
}

//获取发生事件
void epoll_process() {
    for( ; ;) {
        int ready = epoll_wait(epfd, evts, CONNSIZE, -1);
        int i;
        connection_t *c = NULL;
        for(i = 0; i < ready; i++) {
            int revents = evts[i].events;
            c = evts[i].data.ptr;
            if(revents & EPOLLIN) {
                (c->rdhandler)(c);
            }
            if(revents & EPOLLOUT) {
                (c->wrhandler)(c);
            }
        }   
    }
}
