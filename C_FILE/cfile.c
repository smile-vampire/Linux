#include<stdio.h>

int main()
{
  FILE* fp = fopen("tmp.txt","w+");
  if(!fp)
  {
    perror("fopen");
    return 0;
  }
  const char* lp = "linux-66";
  int ret = fwrite(lp,1,sizeof(lp),fp);
  if(ret == 8)
  {
    printf("fp write:%d\n",ret);
  }
  
  fseek(fp,0,SEEK_SET);

  char arr[1024];
  ret = fread(arr,1,sizeof(arr)-1,fp);
  if(ret == 8)
  {
    printf("fp read:%d\n",ret);
  }
  fclose(fp);
}
