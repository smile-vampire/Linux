#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include <pthread.h>

//任务队列节点
typedef struct node {
    void* (*callback)(void* arg);
    void* args;
    struct node *next;
}node_t;
//线程池结构体
typedef struct {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    node_t *head;
    node_t *tail;

    int max_thread;//线程池最多能创建多少线程
    int counter;   //线程池当前线程数
    int idle;      //空闲的线程个数
    int quit;     //如果为1表示销毁线程池
}threadpool_t;

//初始化线程池
void threadpool_init(threadpool_t *pool, int max_thread);

//向线程池中添加任务
void threadpool_add_task(threadpool_t *pool, void *(task)(void*), void *arg);

//销毁线程池
void threadpool_destory(threadpool_t *pool);
#endif
