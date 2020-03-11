//进度条
#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
		int i = 0;
		char a[10] = {0};
		for(i= 0; i < 10; i++)
		{
				a[i] = '-';
				printf("%s\r",a);
				fflush(stdout);
				usleep(100000);
		}

		return 0;
}
