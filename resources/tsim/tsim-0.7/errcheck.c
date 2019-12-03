#include <stdio.h>

int errcheck(i, ec, s)
     int i, ec;
     char *s;
{
  if(i != ec) return(i);
  perror(s);
  exit(1);
}
