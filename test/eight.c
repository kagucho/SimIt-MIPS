#include <stdio.h>

int main()
{
  int i, a, b, c, d, e, x, y;

  a = b = c = d = e = x = y = 0;

  for (i=0; i<200; i++)
    {
      if (i%3==0)
	{
	A:	  
	  a+=1;
	  goto E;
	}
      else
	{
	B:
	  b+=2;
	  if (i%2)
	    {
	    C:
	      c+=3;
	    E:
	      e+=4;
	    }
	  else
	    {
	    D:
	      d+=5;
	    }
	}
    }

  printf ("a:%d b:%d c:%d d:%d e:%d\n", a, b, c, d, e);
  exit (0);
}
