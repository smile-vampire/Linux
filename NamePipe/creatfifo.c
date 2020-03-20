#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
 int ret =  mkfifo("./CFIFO", 0664);
 if(ret < 0)
 {
   perror("fifo");
   return 0;
 }
 //open
 int fd = open("CFIFO", O_RDWR, 0664);
 if(fd < 0)
 {
   perror("open");
   return 0;
 }
 //write
 write(fd, "linux-66", 8);
 //read
 char buf[1024] = {0};
 ret = read(fd, buf, sizeof(buf)-1);
 printf("buf size:[%d]",ret);
 //close
 close(fd);
  return 0;
}
