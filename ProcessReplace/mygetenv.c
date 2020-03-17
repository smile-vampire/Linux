#include<stdio.h>

int main(int argc,char* argv[])
{

  int i = 0;
  for(i = 0; i < argc; i++)
  {
    printf("argv[%d]:%s\n",i,argv[i]);
  }
  extern char** environ;
  for(i = 0; environ[i] ; i++)
  {
    printf("environ[%d]:%s\n",i,environ[i]);
  }
  return 0;
}
