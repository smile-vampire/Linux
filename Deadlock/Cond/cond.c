#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int g_noodle = 0;
pthread_mutex_t lock;
pthread_cond_t cond;
void* ConsumeStar(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    if(g_noodle == 0)
    {
      //没有面要进行阻塞等待，内部解锁，等待唤醒
      pthread_cond_wait(&cond, &lock);
    }
    //有面吃完要解锁
    printf("i eat num %d\n", g_noodle);
    g_noodle--;
    pthread_mutex_unlock(&lock);
    //唤醒厨师做面
    pthread_cond_signal(&cond);
    sleep(1);
  }
  return NULL;
}

void* ProductStar(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    if(g_noodle == 1)
    {
      pthread_cond_wait(&cond, &lock);
    }
    printf("i make num %d\n", g_noodle);
    g_noodle++;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cond, NULL);
  pthread_t tid[2];
  int ret = pthread_create(&tid[0], NULL, ConsumeStar, NULL);
  if(ret < 0)
  {
    perror("pthreadA");
    return 0;
  }
  ret = pthread_create(&tid[1], NULL, ProductStar, NULL);
  if(ret < 0)
  {
    perror("pthreadA");
    return 0;
  }
  int i = 0;
  for(; i < 2; i++)
  {
    pthread_join(tid[i], NULL);
  }
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);
  return 0;
}
