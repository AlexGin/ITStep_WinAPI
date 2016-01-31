#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_TCHAR szBuf3[15] = _TEXT("Hello,");
	_tcscat(szBuf3, _TEXT(" world!"));
	wcout << szBuf3 << '\n';
	cout << "The size of array: " << sizeof(szBuf3) << " bytes\n"; //30 байт
	
	int n = 0;
}

