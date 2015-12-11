
char x=100;
char a[]={'a', 'b', 'd', 'e', '\x55', 's'};
char s[]={'a', 'b', 'd', 'e', '\x55', 's', 0};
char *y="hgij\x40\x41\x42\x43sdsd";
char *z=(char *)100;
char *g=a;

struct aaa {
char a;
int b;
char c;
unsigned d;
} h[]={ {'a',100,'s',2000}, {'c',12000,'d',232322}};

int main()
{
	int c;
	c=a[1];
}
