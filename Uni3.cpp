#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char buffer[] =
		"MultiByteToWideChar converts ANSI-string to Unicode-string";
	// определим размер памяти, необходимый для хранения Unicode-строки
	int length = MultiByteToWideChar(CP_ACP /*ANSI code page*/, 0, buffer,
		-1, NULL, 0);
	wchar_t *ptr = new wchar_t[length];
	// конвертируем ANSI-строку в Unicode-строку
	MultiByteToWideChar(CP_ACP, 0, buffer, -1, ptr, length);
	wcout << ptr << endl;
	cout << "Length of Unicode-string: " << wcslen(ptr) << endl;
	cout << "Size of allocated memory: " << _msize(ptr) << endl;
	delete[] ptr;

	return 0;
}

