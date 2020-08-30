#include <string.h>

//清除右边空格
void rtrim(char *str)
{
  if( str == NULL)
     return;
  int len=strlen(str);

  if(len > 0 && str[len-1]==' ' && str[len-1]=='\r' &&str[len-1]=='\t')
  {
    str[--len]=0;
  }
}

//清楚左边空格
void ltrim(char *str)
{
  if( str == NULL)
      return;
  int len=strlen(str);
  char *ptmp =str;
  if( *ptmp != ' ' )
        return;
  while( *ptmp != '\0')
  {
    if(*ptmp != ' ')
        break;
    ptmp++;
  }
  char *start=str;
  while(*ptmp != '\0')
  {
    *start++=*ptmp++;
  }
  *start='\0';
}
