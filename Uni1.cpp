#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// ANSI-кодировка
	char szBuf1[15] = "Hello,";
	strcat(szBuf1, " world!");
	cout << sizeof(szBuf1) << " bytes\n"; // 15 байт

	// UNICODE-кодировка
	wchar_t szBuf2[15] = L"Hello,";
	wcscat(szBuf2, L" world!");
	cout << sizeof(szBuf2) << " bytes\n"; // 30 байт

	int m = 0;
}
