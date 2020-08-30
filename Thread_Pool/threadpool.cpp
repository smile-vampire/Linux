#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<iostream>
#include<queue>
#include<stdlib.h>

#define THREADCOUNT 4
//线程池：安全队列 + 多个单一线程（消费线程）
//安全队列：
//      元素 + 处理数据的函数地址
typedef void* (*Handler_t)(int);
class threadTask
{
  public:
    threadTask(int data, Handler_t handler)
    {
      _data = data;
      _handler = handler;
    }

    ~threadTask()
    {
      //
    }

    void Run()
    {
      _handler(_data);
    }
  private:
    int _data;
    Handler_t _handler;
};

//线程池
class threadPool
{
  public:
    threadPool()
    {
      _capacity = 10;
      pthread_capacity = THREADCOUNT;
      
      pthread_mutex_init(&_lock, NULL);
      pthread_cond_init(&_cond, NULL);

      bool _create = pthreadCreate();
      if(!_create)
      {
        printf("pthread Create thread failed\n");
        exit(1);
      }
      IsExit = false;
    }

    ~threadPool()
    {

    }

    bool Push(threadTask* tt)
    {
      pthread_mutex_lock(&_lock);
      //当线程退出禁止push数据
      if(IsExit)
      {
        return false;
      }
      _qu.push(tt);
      pthread_mutex_unlock(&_lock);
      //插入数据完成通知线程池当中线程
      //但是如果线程退出，可能还有数据在PCB等待队列也需要退出调用pthreadpoolcancle接口
      pthread_cond_signal(&_cond);
      return true;
    }

    bool Pop(threadTask** tt)
    {
      *tt = _qu.front();
      _qu.pop();
      return true;
    }

    void join()
    {
      for(int i = 0; i < THREADCOUNT; i++)
      {
        pthread_join(tid[i], NULL);
      }
    }
    //如果直接退出线程，可能队列当中还有数据没有处理完毕
    //我们不应该调用该接口来结束线程
    void ThreadExit()
    {
      for(int i= 0; i < THREADCOUNT; i++)
      {
        pthread_cancel(tid[i]);
      }
    }

    void pthreadpoolcancle()
    {
      //变成true
      pthread_mutex_lock(&_lock);
      IsExit = true;
      pthread_mutex_unlock(&_lock);
      //唤醒接口
      pthread_cond_broadcast(&_cond);
    }
  private:
    static void* threadpoolStart(void* arg)
    {
      threadPool* tp = (threadPool*)arg;
      while(1)
      {
        pthread_mutex_lock(&tp->_lock);
        //从队列获取数据进行消费
        threadTask* tt;
        while(tp->_qu.empty())
        {
          if(tp->IsExit)
          {
            pthread_mutex_unlock(&tp->_lock);
            //线程退出
            pthread_exit(NULL);
          }
          pthread_cond_wait(&tp->_cond, &tp->_lock);
        }
        tp->Pop(&tt);
        pthread_mutex_unlock(&tp->_lock);
        //调用队列当中的函数去处理数据
        tt->Run();
        delete tt;
      }
      return NULL;
    }
    //创建线程
    bool pthreadCreate()
    {
      for(int i = 0; i < THREADCOUNT; i++)
      {
        int ret = pthread_create(&tid[i], NULL, threadpoolStart, (void*)this);
        if(ret < 0)
        {
          perror("threadcreate\n");
          return false;
        }
      }
      return true;
    }
  private:
  std::queue<threadTask*>_qu;
   size_t _capacity;//线程池安全队列容量
  
   //互斥锁
   pthread_mutex_t _lock;
   //同步
   pthread_cond_t _cond;

   //线程池初始化线程数量
   size_t pthread_capacity;
   //线程标识符
   pthread_t tid[THREADCOUNT];

   bool IsExit;
};

void* DeleDate(int data)
{
  printf("consum data is %d\n", data);
  return NULL;
}

int main()
{
  threadPool* tp = new threadPool();
  for(int i = 1; i <= 50; i++)
  {
    threadTask* tt = new threadTask(i, DeleDate);
    tp->Push(tt);
  }
  //线程退出
  tp->pthreadpoolcancle();
  //等待线程退出
  tp->join();
  delete tp;
  return 0;
}
