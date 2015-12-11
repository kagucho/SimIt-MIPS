
int main()
{

	int b1,c1, b2, c2;
	int e1, f1, e2, f2;
	unsigned ub1,uc1, ub2, uc2;
	unsigned ue1,uf1, ue2, uf2;

	b1=102,c1=5;
	b2=-102,c2=-5;

	e1=101,f1=7;
	e2=-101,f2=-7;

	ub1 = b1, uc1=c1;
	ub2 = b2, uc2=c2;
	ue1 = e1, uf1=f1;
	ue2 = e2, uf2=f2;

#define op(a,b) a*b
#define o(d) printf("%d ", d);
	o(op(b1,c2));
	o(op(b1,c1));
	o(op(b2,c1));
	o(op(b2,c2));

	o(op(e1,f2));
	o(op(e1,f1));
	o(op(e2,f1));
	o(op(e2,f2));

	printf("\n");

	o(op(ub1,uc2));
	o(op(ub1,uc1));
	o(op(ub2,uc1));
	o(op(ub2,uc2));

	o(op(ue1,uf2));
	o(op(ue1,uf1));
	o(op(ue2,uf1));
	o(op(ue2,uf2));
#undef o


	printf("\n");

	return 0;

}
