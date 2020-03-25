#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sigcallback(int signo)
{
  printf("signo:%d\n",signo);
}

int main()
{
  struct sigaction newact;
  newact.sa_handler = sigcallback;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  struct sigaction oldact;

  sigaction(2, &newact, &oldact);
  while(1)
  {
    sleep(1);
  }
  return 0;
}
