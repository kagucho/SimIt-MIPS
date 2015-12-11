int NUM;
int a[100][100];

void init()
{
  int i, j;
  
  for(i=0; i<NUM; i++)
    for(j=0; j<NUM; j++)
      {
        if((i+j)&7)
	  a[i][j] = i+j;
        else
          a[i][j] = 0;
      }	  
}

int accum()
{
  int i, j;
  int temp = 0;
  
  for(i=0; i<NUM; i++)
    for(j=0; j<NUM; j++)
      if((i+j)&7)
	temp += i+j;
  
  return temp;
}

int accum_or()
{
  int i, j;
  int temp = 0;
  
  for(i=0; i<NUM; i++)
    for(j=0; j<NUM; j++)
      if((i+j)&7 || i>(NUM/2) || j>(NUM/2) )
      {
	temp += i+j;
      }
  
  return temp;
}

int accum_and()
{
  int i, j;
  int temp = 0;
  
  for(i=0; i<NUM; i++)
    for(j=0; j<NUM; j++)
      if((i+j)&7 && i>(NUM/2) && j>(NUM/2) )
	temp += i+j;
  
  return temp;
}

/* The funny_calls test for parameter passing quirks...what goes on the
   memory stack and what goes in the registers. */

char funny_call1(int a, short b, char c, int d, short e, char f, int g){
  return (int)(a+b+c+d+e+f+g);
}

char funny_call2(int a, short b, char c, int d, short e){
  return (int)(a+b+c+d+e);
 }

int main()
{
  int i, j;
  
  NUM = 20;  
  init();
  
  for(i=0; i<NUM; i++)
    for(j=0; j<NUM; j++)
      printf("%ld\n", a[i][j]);
  
  printf("%ld\n", accum());
  printf("%ld\n", accum_or());
  printf("%ld\n", accum_and());
  printf("%lf\n", funny_call1(1, 1, 1, 2, 2, 2, 3));
  printf("%lf\n", funny_call2(4, 4, 4, 5, 5));

  return 0;
}
