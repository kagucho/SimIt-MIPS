#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int i,s,n;

  if (argc < 2) {
    printf("Usage: fact2 <n>\n");
    exit(1);
  }
  n = atoi(argv[1]);

  for (i=1, s=1 ; i <= n ; i++) s *= i;
  printf("fact %d = %d\n", (i-1), s);
  exit(0);
}

  
