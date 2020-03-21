#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>

#define shm_key 0x99999999

int main()
{
  int shmid = shmget(shm_key, 1024, IPC_CREAT | 0664);
  if(shmid < 0)
  {
    perror("shmid");
    return 0;
  }
  
  struct shmid_ds buf;
  shmctl(shmid, IPC_STAT, &buf);
  printf("shm_size:[%ld]\n",buf.shm_segsz);

  void* lp = shmat(shmid, NULL, 0);
  if(!lp)
  {
    perror("shmat");
    return 0;
  }

  while(1)
  {
    printf("readshm read [%s]\n",(char*)lp);
    sleep(1);
  }

  shmdt(lp);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
