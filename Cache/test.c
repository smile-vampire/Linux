#include<stdio.h>
#include<unistd.h>

int main()
{
  //printf("linux-66");函数return刷新
  //printf("linux-66\n");\n刷新缓冲区
//  while(1)
// {
//    printf("linux-66");//缓冲区写满刷新缓冲区
//    usleep(10000);
//  }
  printf("linux-66");
  fflush(stdout);//fflush手动刷新
  sleep(5);
  
  return 0;
}
