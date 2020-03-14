#include<stdio.h>
#include<stdlib.h>
int main()
{
		char* path = getenv("PATH");
		printf("path = [%s]\n",path);
		return 0;
}
