#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
  int fd[2];
  int ret = pipe(fd);
  if(ret < 0)
  {
    perror("pipe");
    return 0;
  }
  
  int flags = fcntl(fd[0], F_GETFL, 0);
  flags |= O_NONBLOCK;
  fcntl(fd[0], F_SETFL, flags);

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
   // sleep(3);
  // close(fd[0]);
  close(fd[1]);
    char buf[1024] = {0};
    int retsize = read(fd[0],buf,sizeof(buf)-1);
    if(retsize < 0)
    {
      perror("readsize:\n");
      printf("readsize:%d\n",retsize);
      exit(0);
    }

    printf("size is [%d]\n",retsize);
    printf("i am chile i read buf [%s]\n",buf);
    while(1)
    {
      sleep(1);
    }
  }

  //father 写
  //write(fd[1],"linux-66", 8);
 // close(fd[0]);
 // int count = 0;
 // while(1)
 // {
 //  int ret = write(fd[1], "6", 1);
 //  if(ret < 0)
 //  {
 //    perror("write");
 //    break;
 //  }
 //   count++;
 //   printf("write size [%d]\n", count);
 // }
 
  close(fd[1]);
  while(1)
  {
    printf("i am father\n");
    sleep(1);
  }


  return 0;
}
