/* The Matrix Multiply computation.

   Creates and  multiplies two matrices and sums up all the elements
   of the resulting matrices. 

   October 31, 1995
   Shail Aditya.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE];
int NUM;

int main (int argc, char *argv[])
{
  int i,j,k;
  int s1,s2;

  if (argc < 2) {
    printf("Usage: mm_int <size>\n");
    exit(1);
  }
  NUM = atoi(argv[1]);

  for (i=0 ; i < NUM ; i++) 
    for (j=0 ; j < NUM ; j++)
      a[i][j] = b[i][j] = i+j;

  for (i=0 ; i < NUM ; i++) 
    for (j=0 ; j < NUM ; j++) {
      s1 = 0;
      printf("i = %d, j = %d \n", i, j);fflush(stdout);
      for (k=0; k < NUM ; k++)
	s1 += a[i][k]*b[k][j];
      c[i][j] = s1;
    }

  for (i=0, s1=0 ; i < NUM ; i++) {
    for (j=0, s2=0 ; j < NUM ; j++) s2 += c[i][j];
    s1 += s2;
  }
  printf("sum = %d\n", s1);
  exit(0);
}
