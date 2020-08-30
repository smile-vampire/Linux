#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define THREADCOUNT 4

int g_tickes = 100;

pthread_mutex_t lock;

void* thread_star(void* arg)
{
  (void)arg;
  while(1)
  {
    //访问临界资源之前进行加锁
    pthread_mutex_lock(&lock);
    if(g_tickes > 0)
    {
      g_tickes--;
      usleep(100000);
      printf("i am thread [%p], i have ticket num is [%d]\n",pthread_self(),g_tickes+1);
    }
    else{
      //所以有可能退出的地方都需要解锁
      pthread_mutex_unlock(&lock);
      break;
    }
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main()
{
  //在创建线程之前初始化
  pthread_mutex_init(&lock, NULL);
  pthread_t tid[THREADCOUNT];
  int i = 0;
  for(; i< THREADCOUNT; i++)
  {
    int ret = pthread_create(&tid[i], NULL, thread_star, NULL);
    if(ret < 0)
    {
      perror("pthread_create");
      return 0;
    }
  }

  for(i = 0; i < THREADCOUNT; i++)
  {
    pthread_join(tid[i], NULL);
  }
  //在线程用完时进行释放
  pthread_mutex_destroy(&lock);
  return 0;
}
