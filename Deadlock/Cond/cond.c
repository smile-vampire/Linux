#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define THREADCOND 2
int g_noodle = 0;
pthread_mutex_t lock;
//pthread_cond_t cond;
pthread_cond_t Consum_cond;
pthread_cond_t Product_cond;
void* ConsumeStar(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(g_noodle == 0)
    {
      //没有面要进行阻塞等待，内部解锁，等待唤醒
      pthread_cond_wait(&Consum_cond, &lock);
    }
    //有面吃完要解锁
    g_noodle--;
    printf("i consum num %d\n", g_noodle);
    pthread_mutex_unlock(&lock);
    //唤醒厨师做面
    pthread_cond_signal(&Product_cond);
  }
  return NULL;
}

void* ProductStar(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(g_noodle == 1)
    {
      pthread_cond_wait(&Product_cond, &lock);
    }
    g_noodle++;
    printf("i product num %d\n", g_noodle);
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&Consum_cond);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&lock, NULL);
  //pthread_cond_init(&cond, NULL);
  pthread_cond_init(&Consum_cond, NULL);
  pthread_cond_init(&Product_cond, NULL);
  pthread_t Consum_tid[THREADCOND];
  pthread_t Product_tid[THREADCOND];
  int i = 0;
  int ret = -1;
  for(i = 0; i < THREADCOND; i++)
  {
    ret = pthread_create(&Consum_tid[i], NULL, ConsumeStar, NULL);
    if(ret < 0)
    {
      perror("pthreadA");
      return 0;
    }
  }
  for(i = 0; i < THREADCOND; i++)
  {  
    ret = pthread_create(&Product_tid[i], NULL, ProductStar, NULL);
    if(ret < 0)
    {
      perror("pthreadA");
      return 0;
    }
  }
  for(i= 0; i < THREADCOND; i++)
  {
    pthread_join(Consum_tid[i], NULL);
    pthread_join(Product_tid[i], NULL);
  }
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&Consum_cond);
  pthread_cond_destroy(&Product_cond);
 // pthread_cond_destroy(&cond);
  return 0;
}
