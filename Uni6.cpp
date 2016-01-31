#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	wchar_t buffer[] = L"wcstombs converts Unicode-string to ANSI-string";
	// определим размер памяти, необходимый для хранения преобразованной 
	// ANSI-строки
	int length = std::wcstombs(NULL, buffer, 0);
	char *ptr = new char[length + 1];
	// конвертируем Unicode-строку в ANSI-строку 
	std::wcstombs(ptr, buffer, length + 1);
	cout << ptr;
	cout << "\nLength of ANSI-string: " << strlen(ptr) << endl;
	cout << "Size of allocated memory: " << _msize(ptr) << " bytes" << endl;
	delete[] ptr;
	
	return 0;
}

