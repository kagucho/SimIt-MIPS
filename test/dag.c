#include <stdio.h>

int main()
{
  int i,a,b,c,d,e,f,g;

  a=b=c=d=e=f=g=0;
  for (i=0; i<200; i++)
    {
      a++;
      if (i%2==0)
	{
	  b++;
	  if (i%4==0)
	    c++;
	  else
	    d++;
	}
      else
	{
	  e++;
	  if (i%4==1)
	    f++;
	  else
	    g++;
	}
    }
  printf("a:%d b:%d c:%d d:%d e:%d f:%d g:%d\n", a,b,c,d,e,f,g);
  exit(0);
}
