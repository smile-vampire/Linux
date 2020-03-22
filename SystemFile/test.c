#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
  int fd = open("./tmp.txt", O_RDWR | O_CREAT, 0664);
  if(fd < 0)
  {
    perror("open");
    return 0;
  }
  printf("fd:[%d]\n",fd);
  while(1)
  {
    sleep(1);
  }
  return 0;
}
