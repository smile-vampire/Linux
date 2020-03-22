#include<stdio.h>
#include<unistd.h>


int main()
{
  printf("printf");
  fwrite("fwrite", 1, 6, stdout);
  fprintf(stdout, "%s%s", "fprintf", "66");
  write(1,"write",5);
  sleep(5);
  return 0;
}
