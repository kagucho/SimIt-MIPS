/* The Fibonacci number computation.

   Computes a fibonacci number using a linear recurrence.

   October 31, 1995
   Shail Aditya.
*/

#include <stdio.h>
#include <stdlib.h>
int a[100];


int main (int argc, char *argv[])
{
  int i,n;

  if (argc < 2) {
    printf("Usage: fib <n>\n");
    exit(1);
  }
  n = atoi(argv[1]);

  a[0] = 0;
  a[1] = 1;
  for (i=2 ; i <= n ; i++)
    a[i] = a[i-1] + a[i-2];
  printf("fib %d = %d\n", n, a[n]);
  exit(0);
}
