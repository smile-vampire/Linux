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
		if(ret < 0)
		{
				perror("fork");
				return 0;
		}
		else if(ret == 0)
		{
				//child 读
				char buf[1024] = {0};
		//		read(fd[0],buf,sizeof(buf)-1);
		//		printf("i am child i read buf[%s]\n",buf);
				//1.管道当中没有数据了，read就会阻塞
				//2.管道当中的数据被拿走了
		//		read(fd[0],buf,sizeof(buf)-1);
				while(1)
				{
						sleep(1);
				}
		}
		//father 写
		//write(fd[1],"linux-66",8);
		int count = 0;
		while(1)
		{
				write(fd[1],"6",1);
				count++;
				printf("%d\n",count);
		}

		return 0;
}
