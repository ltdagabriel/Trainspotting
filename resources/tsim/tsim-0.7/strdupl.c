#include <string.h>
#ifdef LINUX
#include <stdlib.h> 
#endif

char *strdupl(s)
     char *s;
{
  char *s_copy;
  if(!(s_copy = (char *)malloc(strlen(s)+1)))
     return((char *)0);
  return(strcpy(s_copy, s));
}
