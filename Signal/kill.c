#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main()
{
  printf("我要结束了\n");
  //kill(getpid(), 2);
  int* p = NULL;
  *p = 10;
  alarm(3);
  while(1)
  {
    printf("如果打印就错误\n");
    sleep(1);
  }
  return 0;
}
