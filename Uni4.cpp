#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char buffer[] = "mbstowcs converts ANSI-string to Unicode-string";
	// определим размер памяти, необходимый для хранения Unicode-строки
	int length = std::mbstowcs(NULL, buffer, 0);
	wchar_t *ptr = new wchar_t[length];
	// конвертируем ANSI-строку в Unicode-строку
	std::mbstowcs(ptr, buffer, length);
	wcout << ptr;
	cout << "\nLength of Unicode-string: " << length << endl;
	cout << "Size of allocated memory: " << _msize(ptr) << " bytes" << endl;
	delete[] ptr;
	
	return 0;
}

