int cfg1(int k, int l);
int cfg2(char k, float j);
float cfg3(int j, int y);
int cfg21(int k, int l);
int cfg22(char k, float j);
float cfg23(int j, int y);
int cfg222(char k, float j);
int SOF()
{
	char s[] = "123456789";
	char d[] = "123";
	strcpy(d, s);
	printf("result: %s, \n%s", d, s);
}

int func(int j)
{
	int dodo;
	//abcdefg 
	int cfg1(int j, int dodo);
	return dodo;
}

int cfg2(char k, float j)
{
	int dodo;
	int cfg1(int j, int dodo);
	//dodo = func(j);
}
//But we were born to be alone
//Yeah we were born to be alone
//Yeah we were born to be alone
//But why we still looking for love
int HOF(int argc, char* argv[])
{
	char mybuf1[450];
	HANDLE hHeap;
	char* buf1;
	char* buf2;
	int i;

	for (int i = 0; i < 450; i++) {
		mybuf1[i] = ’a’;
	}
	LoadLibrary("user32");
	hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0x10000, 0xfffff);
	buf1 = (char*)HeapAlloc(hHeap, 0, 200);
	strcpy(mybuf1, buf1);
	buf2 = (char*)HeapAlloc(hHeap, 0, 200);
	HeapFree(hHeap, 0, buf1);
	HeapFree(hHeap, 0, buf2);
	return 0;
}

int HOF(int argc, char* argv[])
{
	char mybuf2[450];
	HANDLE hHeap;
	char* buf1;
	char* buf2;
	for (int i = 0; i < 450; i++) {
		mybuf2[i] = ’a’;
	}
	LoadLibrary("user32");
	hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS, 0x10000, 0xfffff);
	buf1 = (char*)HeapAlloc(hHeap, 0, 200);
	strcpy(buf1, mybuf2);
	buf2 = (char*)HeapAlloc(hHeap, 0, 200);
	HeapFree(hHeap, 0, buf1);
	HeapFree(hHeap, 0, buf2);
	return 0;
}
int func2(int j)
{
	int dodo;
	//abcdefg 
	int cfg21(int j, int dodo);
	/*lalalalalalalal
	aaaaaaaaaaaaaaaaa
	Liiiiiiiiiiiiiiii
	Saaaaaaaaaaaaaaa
	Lalisa*/
	return dodo;
}

int cfg22(char k, float j)
{
	int dodo;
	int cfg21(int j, int dodo);
	//dodo = func(j);
}

/*栈溢出：7.cpp
堆溢出：8.cpp
宽度：b2.cpp
运算：b3.cpp
符号：b4.cpp
格式化：r5.cpp

样本库！！！！

50个样本(每个100行以上)每10个为相似的一组，1分，最高5分

漏洞检测与同源性检测样本库，样本数量不少于10个，
每个代码行数不少于100行；每种漏洞至少一个。*/
int gsh()
{
	int a;
	int b;
	char buf[80] = "hahaha";
	printf("%s%d%d%x", buf, a, b);

}