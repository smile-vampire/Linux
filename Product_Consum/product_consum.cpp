#include<cstdio>
#include<unistd.h>
#include<iostream>
#include<pthread.h>
#include<queue>

#define THREADCOUNT 2

class BlockQueue
{
  public:
    BlockQueue(size_t Capacity)
    {
      Capacity_ = Capacity;

      pthread_mutex_init(&Mutex_, NULL);
      pthread_cond_init(&ConsumCond_, NULL);
      pthread_cond_init(&ProductCond_, NULL);
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&Mutex_);
      pthread_cond_destroy(&ConsumCond_);
      pthread_cond_destroy(&ProductCond_);
    }

    void Push(int& Date)
    {
      pthread_mutex_lock(&Mutex_);
      while(Isfull())
      {
        pthread_cond_wait(&ProductCond_, &Mutex_);
      }
      Queue_.push(Date);
      pthread_mutex_unlock(&Mutex_);
      pthread_cond_signal(&ConsumCond_);
    }

    void Pop(int* Date)
    {
      pthread_mutex_lock(&Mutex_);
      while(Queue_.empty())
      {
        pthread_cond_wait(&ConsumCond_, &Mutex_);
      }
      *Date = Queue_.front();
      Queue_.pop();
      pthread_mutex_unlock(&Mutex_);
      pthread_cond_signal(&ProductCond_);
    }
  private:
    bool Isfull()
    {
      if(Queue_.size() == Capacity_)
      {
        return true;
      }
      return false;
    }
  private:
    std::queue<int> Queue_;
    size_t Capacity_;
    //互斥
    pthread_mutex_t Mutex_;
    //同步 两种角色
    pthread_cond_t ConsumCond_;
    pthread_cond_t ProductCond_;

};

void* ConsumStar(void* arg)
{
  BlockQueue* bq = (BlockQueue*)arg;
  while(1)
  {
    int Date;
    bq->Pop(&Date);

    printf("ConsumStar [%p][%d]\n",pthread_self(),Date);
  }
  return NULL;
}

void* ProductStar(void* arg)
{
  BlockQueue* bq = (BlockQueue*)arg;
  int i = 0;
  while(1)
  {
    bq->Push(i);

    printf("ProductStar [%p][%d]\n",pthread_self(),i);
    i++;
  }
  return NULL;
}

int main()
{
  BlockQueue* bq = new BlockQueue(10);

  pthread_t comtid[THREADCOUNT], protid[THREADCOUNT];
  int i = 0;
  for(; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&comtid[i], NULL, ConsumStar, (void*)bq);
    if(ret < 0)
    {
      perror("pthread create failed\n");
      return 0;
    }


    ret = pthread_create(&protid[i], NULL, ProductStar, (void*)bq);
    if(ret < 0)
    {
      perror("pthread create failed\n");
      return 0;
    }
  }

  for(i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(comtid[i], NULL);
    pthread_join(protid[i], NULL);
  }

  delete bq;
  bq = NULL;
  return 0;
}
