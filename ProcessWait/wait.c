#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0)
  {
    perror("fork");
    return 0;
  }
  else if(pid == 0)
  {
    //child
    printf("i am child\n");
//    while(1)
//    {
//      printf("我给你讲！\n");
//      sleep(1);
//    }
    exit(1);
  }
  else{
    //father
    //再fork一个子进程，让该子进程也退出
    pid_t pid2 =fork();
    if(pid2 < 0)
    {
      return 0;
    }
    else if(pid2 == 0)
    {
      //child
      exit(9);
    }
    int status;
    int ret = wait(&status);
    wait(NULL);
    printf("status[%d][%d]\n",status,ret);
    while(1)
    {
      printf("我不听!\n");
      sleep(1);
    }
  }
  return 0;
}
