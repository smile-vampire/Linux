#include<stdio.h>
#include<unistd.h>

int main()
{
  //ret = execl("/usr/bin/ls","ls","-l",NULL);
  //printf("ret : %d\n",ret);
  //int ret = execlp("mygetenv","mygetenv","-l","-a","-b",NULL);
  //printf("ret : %d\n",ret);
  
  char* envp[3];
  envp[0] = "PATH=hahahha";
  envp[1] = "MYPATH=mygetenv";
  envp[2] = NULL;
  //execle("./mygetenv","mygetenv","-a","-b","-c",NULL,NULL);
  
  char* argv[3];
  argv[0] = "mygetenv";
  argv[1] = "-a";
  argv[2] = NULL;
  //execv("./mygetenv",argv);
  
  //execvp("mygetenv",argv);
  execve("mygetenv",argv,envp);
  printf("linux-66\n");
  return 0;
}
