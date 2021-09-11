void widt()
{
	unsigned short s;
	int i;
	char buf[80];
	s = i;
	if (s >= 80)
		return;
	memcpy(buf, argv[2], i);
}

void calc()
{
	unsigned short s;
	int i;
	short m;
	char buf[80];
	s = i * m;
	memcpy(buf, argv[2], s);
}

void sym()
{
	unsigned short s;
	int i;
	char buf[80];
	s = i;
	if (s >= 80)
		return;
	memcpy(buf, argv[2], -1);
}

int gsh()
{
	int a;
	int b;
	char buf[80] = "hahaha";
	printf("%s%d%d%x", buf, a, b);

}