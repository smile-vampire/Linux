#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

typedef struct thread_info{
  int thread_num;
  thread_info()
  {
    thread_num = -1;
  }

}THREADINFO;

void* thread_start(void* arg)
{
  THREADINFO* ti = (THREADINFO*)arg;
  while(1)
  {
    printf("i am new pthread%d\n",ti->thread_num);
    sleep(1);
  }
  //对于传递进来的堆上开辟的内存，可以在线程入口函数结束时，释放掉，不会导致程序内存泄露的风险
  delete ti;
  return NULL;
}

int main()
{
  pthread_t tid;
  int ret;
//  {
//    //i 是临时变量
//    int i = 10;
//    ret =  pthread_create(&tid, NULL, thread_start, (void*)&i);
//  }
  int i = 0;
  for(; i < 4; i++)
  {
    //堆上开辟
    THREADINFO* threadinfo = new thread_info();
    threadinfo->thread_num = i;
    ret = pthread_create(&tid, NULL, thread_start, (THREADINFO*)threadinfo);
    if(ret < 0)
    {
      perror("pthread");
      return 0;
    }
  }
  while(1)
  {
    printf("i am main pthread\n");
    sleep(1);
  }
  return 0;
}
