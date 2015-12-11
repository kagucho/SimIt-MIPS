#include <stdio.h>

int main()
{
  int i, a, b, c;

  a = b = c = 0;

  for (i=0; i<200; i++)
    {
      a+=1;
      if (i%10==0) continue;
      b+=2;
      if (i%10==5) continue;
      c+=3;
    }

  printf ("a:%d b:%d c:%d\n", a, b, c);
  exit (0);
}
