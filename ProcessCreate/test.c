#include<stdio.h>
#include<unistd.h>
int main()
{
		//创建子函数
		//系统调用函数
		printf("linux66\n");
		pid_t pid = fork();
		if(pid < 0)
		{
				//没有内存的时候可能报错，创建PCB是需要耗费内存，用的是内核空间
				perror("fork");
				return 0;
		}
		else if(pid == 0)
		{
				//child
		printf("i am child:[%d]-[%d]\n",getpid(),getppid());
		}
		else
		{
				//father
		printf("i am father:[%d]-[%d]\n",getpid(),getppid());
				while(1)
				{		sleep(1);
						printf("我不听\n");
				}
		}

		//获取当前进程的pid，我们要使用getpid
		//会哦去当前进程的父进程的pid，我们需要使用getppid
		return 0;
}
