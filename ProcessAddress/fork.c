#include<stdio.h>
#include<unistd.h>

int g_val = 10;
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
    g_val = 100;
    printf("child=[%d]:[%d],g_val=[%d],%p\n",getpid(),getppid(),g_val,&g_val);
  } 
  else
  {
    sleep(2);
    printf("father=[%d]:[%d],g_val=[%d],%p\n",getpid(),getppid(),g_val,&g_val);
  }
  return 0;
}
