#include<stdio.h> 
int main()
{ 
  int count = 0;
  while(1)
  {
    FILE* fp = fopen("tmp.txt","w+");
    if(!fp)
    {
      printf("fopen open failed [%d]\n",count);
      return 0;
    }
    count++;
  }
  return 0;

}
