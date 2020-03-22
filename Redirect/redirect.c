#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
  int fd = open("tmp.txt", O_RDWR | O_CREAT, 0664);
  if(fd < 0)
  {
    perror("open");
    return 0;
  }
  //重定向
  //通过重定向，将本应该输出在标准输出上的上的内容输出到文件当中去
  dup2(fd,1);
  printf("%s\n","linux-66");
  while(1)
  {
    sleep(1);
  }
  return 0;
}
