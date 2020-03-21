#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#define shm_key 0x99999999

int main()
{
  int shmid = shmget(shm_key, 1024, IPC_CREAT | 0664);
  if(shmid < 0)
  {
    perror("shmget");
    return 0;
  }

  void* lp = shmat(shmid, NULL, 0);
  if(!lp)
  {
    perror("shmat");
    return 0;
  }
  int i = 0;
  while(1)
  {
    sprintf((char*)lp, "%s-%d", "linux", i);
    i++;
    sleep(1);
  }
  //shmdt(lp);
  //shm(lp, IPC_RMID, NULL)
  return 0;
}
