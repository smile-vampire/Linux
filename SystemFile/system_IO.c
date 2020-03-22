#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
  int fd = open("tmp.txt",O_RDWR | O_CREAT | O_APPEND, 0664);
  if(fd < 0)
  {
    perror("open");
    return 0;
  }

  int ret = write(fd, "linux-66", 8);
  if(ret < 0 )
  {
    perror("write");
    return 0;
  }

  lseek(fd,0,SEEK_SET);

  //读
  char buf[1024] = {0};
  ret = read(fd,buf,sizeof(buf)-1);
  if(ret < 0)
  {
    printf("read");
    return 0;
  }
  else if(ret == 0)
  {
    printf("read size [%d]\n",ret);
  }
  printf("%s\n",buf);
  close(fd);
  return 0;
}
