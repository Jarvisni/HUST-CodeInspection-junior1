int cfg1(int x, int y);
short cfg2(int x);
long cfg3( );


int main( )
{
	int n_1 = 1, n_2 = 2, n_3 = 3;
	short t_1;

	n_1 = cfg1(n_2, n_3);
	t_1 = cfg1(&n_1);

	return 0;
}

int cfg1(int x, int y)
{
	int z = x + y;
	cfg3( );
	return z;
}

short cfg2(int x)
{
	x = 4;
	return 4;
}

long cfg3( )
{
	long m;
	return tt;
}
