#include<stdio.h>
#include <unistd.h>

int main()
{

		pid_t pid = fork();
		if(pid < 0)
		{
				return pid;
		}

		extern char** environ;

		printf("environ[0] = [%s], pid = [%d], ppid = [%d]\n", environ[0], getpid(), getppid());
		//for(int i = 0; environ[i]; i++)
		//    //{
		//            printf("environ[%d] = [%s]\n", i, environ[i]);
		//      }
		return 0;
}
