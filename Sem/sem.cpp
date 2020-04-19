#include<cstdio>
#include<unistd.h>
#include<iostream>
#include<pthread.h>
#include<vector>
#include<semaphore.h>

#define SIZE 1
#define THREADCOUNT 1

class RingQueue
{
  public:
    RingQueue()
      :Vec_(SIZE)
    {
      Capacity_ = SIZE;
      Posread_ = 0;
      Poswrite_ = 0;

      sem_init(&Lock, 0, 1);
      sem_init(&ProSem_, 0, SIZE);
      sem_init(&ConSem_, 0, 0);
    }

    ~RingQueue()
    {
      sem_destroy(&Lock);
      sem_destroy(&ProSem_);
      sem_destroy(&ConSem_);
    }

    void Push(int& Date)
    {
      sem_wait(&ProSem_);
      sem_wait(&Lock);
      Vec_[Poswrite_] = Date;
      Poswrite_ = (Poswrite_ + 1) % Capacity_;
      sem_post(&Lock);
      sem_post(&ConSem_);
    }

    void Pop(int* Date)
    {
      sem_wait(&ConSem_);
      sem_wait(&Lock);
      *Date = Vec_[Posread_];
      Posread_ = (Posread_ + 1) % Capacity_;
      sem_post(&Lock);
      sem_post(&ProSem_);
    }
  private:
    std::vector<int> Vec_;
    size_t Capacity_;

    int Poswrite_;
    int Posread_;

    //同步
    sem_t ConSem_;
    sem_t ProSem_;

    //互斥
    sem_t Lock;
        
};

void* ProductStar(void* arg)
{
  RingQueue* rq = (RingQueue*)arg;
  int i = 0; 
  while(1)
  {
    rq->Push(i);
    printf("ProductStar [%p][%d]\n",pthread_self(),i);
    i++;
  }
  return NULL;
}

void* ConsumStar(void* arg)
{
  RingQueue* rq = (RingQueue*)arg;
  int Data;
  while(1)
  {
     rq->Pop(&Data);
     printf("ConsumeStart [%p][%d]\n", pthread_self(), Data);
  }
     return NULL;
}

int main()
{
  RingQueue* rq = new RingQueue();

  pthread_t contid[THREADCOUNT], protid[THREADCOUNT];
  int i = 0;
  for(; i < THREADCOUNT; i++)
  {
    int ret = pthread_create(&protid[i], NULL, ProductStar, (RingQueue*)rq);
    if(ret < 0)
    {
      perror("pthread create failed\n");
      return 0;
    }

    ret = pthread_create(&contid[i], NULL, ConsumStar, (RingQueue*)rq);
    if(ret < 0)
    {
      perror("pthread create failed\n");
      return 0;
    }
  }

  for(i = 0; i< THREADCOUNT; i++)
  {
    pthread_join(protid[i], NULL);
    pthread_join(contid[i], NULL);
  }

  delete rq;
  rq = NULL;
  return 0;
}
