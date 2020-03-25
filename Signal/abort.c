#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int main()
{
  printf("aaaaaa\n");
  abort();
  while(1)
  {
    printf("bbbbbbb\n");
    sleep(1);
  }
  return 0;
}
