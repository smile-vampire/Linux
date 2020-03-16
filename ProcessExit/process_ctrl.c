#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

  void func()
  {
    printf("bay-bay\n");
  }

int main()
{
  atexit(func);
  //_exit(99);
  printf("linux-66");
  //fflush(stdout);
  sleep(3);
  exit(-1);
  return 0;
}
