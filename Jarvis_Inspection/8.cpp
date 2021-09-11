int HOF(int argc, char* argv[])
{
	char mybuf1[450];
	HANDLE hHeap;
	char* buf1;
	char* buf2;
	int i;

	for (int i = 0; i < 450; i++) {
		mybuf1[i] = ¡¯a¡¯;
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
		mybuf2[i] = ¡¯a¡¯;
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