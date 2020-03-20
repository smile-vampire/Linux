#include<stdio.h>
#include<unistd.h>

int main()
{
  int fd[2];
  int ret = pipe(fd);
  if(ret < 0)
  {
    perror("pipe");
    return 0;
  }

  //创建子进程
  ret = fork();
  if(ret < 0 )
  {
    perror("fork");
    return 0;
  }
  else if (ret == 0)
  {
    //child 读
    sleep(3);
    char buf[1024] = {0};
    read(fd[0],buf,sizeof(buf)-1);
    printf("i am chile i read buf [%s]\n",buf);
    while(1)
    {
      sleep(1);
    }
  }

  //father 写
  write(fd[1],"linux-66", 8);
  while(1)
  {
    sleep(1);
  }
  close(fd[0]);
  close(fd[1]);
  return 0;
}
