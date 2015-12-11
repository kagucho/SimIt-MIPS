/* The Fibonacci number computation.

   Computes a fibonacci number using a linear recurrence.

   October 31, 1995
   Shail Aditya.
*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int i, f1, f2, N;
  int f = 0;

  if (argc < 2) {
    printf("Usage: fib <n>\n");
    exit(1);
  }
  N = atoi(argv[1]);

  switch (N) {
  case 0: f = 0; break;
  case 1: f = 1; break;
  default: 
    for (i=2, f1=0, f2=1; i <= N ; i++) {
      f = f1+f2;
      f1 = f2;
      f2 = f;
    }
  }
  //printf("fib %d = %d\n", N, f);
  printf("fib %d", N);
  printf(" = %d\n", f);
  exit(0);
}
