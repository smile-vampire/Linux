#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* thread_star(void* arg)
{
  (void)arg;
  printf("i am new pthread\n");
  //sleep(20);
  sleep(5);
  //printf("pthread exit\n");
  //谁调用谁退出
  //pthread_exit(NULL);
  //printf("pthread cancel:%p\n",pthread_self());
  //pthread_cancel(pthread_self());
  while(1)
  {
    sleep(1);
    printf("11111111\n");
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, thread_star, NULL);
  if(ret < 0)
  {
    perror("thread\n");
    return 0;
  }

  sleep(5);
  //程序不会退出，主线程变成僵尸状态
  pthread_exit(NULL);
  //pthread_cancel(tid);
  pthread_join(tid, NULL);//阻塞等待
  while(1)
  {
    printf("i am main pthread\n");
    sleep(1);
  }
  return 0;
}
