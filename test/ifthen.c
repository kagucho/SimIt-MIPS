#include <stdio.h>

int main()
{
  int i,a,b,c,d,e,f,g;

  a=b=c=d=e=f=g=0;
  for (i=0; i<200; i++) {
    int x = i%2;
    int y = i%4;
    a++;
    if (x==0) {
      b++;
      if (y==0) {
	c++;
      } else {
	d++;
      }
    } else {
      e++;
    }
    if (x==0) {
      f++;
    } else {
      g++;
    }
  }
  printf("a:%d b:%d c:%d d:%d e:%d f:%d g:%d\n", a,b,c,d,e,f,g);
  exit(0);
}
