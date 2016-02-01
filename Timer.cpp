// Timer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "CWnd.h"
#include "resource.h"
using namespace std;


#define MAX_LOADSTRING 100

#define UM_START WM_USER+1		//коды пользовательских сообщений
#define UM_STOP WM_USER+2		//
#define TIMER_SEC 1			//идентификатор таймера

HINSTANCE g_hInstance;

HWND hDlg;
static RECT rect;
static POINT center, current;
static int width, height;
int label = 0;				//для хранения текущей секунды в формате int
FLOAT startAngle = 90, sweepAngle = 0;	//начальный угол и приращение угла для AngleArc()

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	// setlocale(LC_ALL, "ru-RU");

	g_hInstance = hInstance;

	MSG msg;
	CWnd mainWnd(TEXT("Секундомер"), hInstance, nCmdShow, WndProc, NULL, 100, 100, 700, 400, CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;	
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	HBRUSH hBrush, hBrushOld;
	HPEN hPen, hPen1, hPenOld;
	PAINTSTRUCT ps;
	int userReply;
	TCHAR buf[15] = TEXT("");

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
		GetClientRect(hWnd, &rect);
		center.x = (rect.right - rect.left) / 2;	//определяем центр клиентской области
		center.y = (rect.bottom - rect.top) / 2;
		width = center.x / 2;					//определяем области для рисования
		height = center.y / 2;					//циферблата
		hBrush = CreateSolidBrush(RGB(200, 160, 255));	//невидимая кисть
		hBrushOld = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 190, 0)); //перо для рисования окружности и стрелки
		hPen1 = CreatePen(PS_SOLID, 5, RGB(200, 160, 255)); //невидимое перо для рисования дуги
		hPenOld = (HPEN)SelectObject(hDC, hPen);

		Ellipse(hDC, center.x - height, center.y - height, center.x + height, center.y + height);
		MoveToEx(hDC, center.x, center.y, NULL);	//переносим перо
		hPenOld = (HPEN)SelectObject(hDC, hPen1);		//вставляем в DC перо для рисования дуги
		AngleArc(hDC, center.x, center.y, height + 10, startAngle, -sweepAngle);

		GetCurrentPositionEx(hDC, &current);
		DeleteObject(SelectObject(hDC, hPenOld)); //возвращаем в DC предыдущее перо

		LineTo(hDC, center.x, center.y);	//рисуем стрелку уже видимым пером

		wsprintf(buf, TEXT("%d"), label / 6);	//отсчитанные секунды в buf из int в TCHAR

		if (label / 6 >= 0 && label / 6 <= 10)	//определяем (на глаз :)) место для вывода 
		{							//метки с отсчитанными секундами
			current.y -= 10;
		}
		if (label / 6>10 && label / 6 <= 30)
		{
			current.x += 10;
		}
		if (label / 6>21 && label / 6 <= 37)
		{
			current.x += 0;
			current.y += 10;
		}

		TextOut(hDC, current.x, current.y, (LPCWSTR)buf, wcslen(buf)); //нарисовать текущую секунду

		DeleteObject(SelectObject(hDC, hBrushOld));
		DeleteObject(SelectObject(hDC, hPenOld));

		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		SetClassLong(hWnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(200, 160, 255)));
		hDlg = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		break;
	case WM_LBUTTONDOWN:
		DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DlgProc);
		break;
	case UM_START:
		SetTimer(hWnd, TIMER_SEC, 1000, NULL);
		InvalidateRect(hWnd, &rect, TRUE);
		break;
	case WM_RBUTTONDBLCLK:
		if (wParam & MK_CONTROL)
		{
			PostMessage(hWnd, UM_START, 0, 0);
			break;
		}
	case UM_STOP:
		KillTimer(hWnd, TIMER_SEC);
		InvalidateRect(hWnd, &rect, TRUE);
		break;

	case WM_TIMER:
		switch (wParam) {
		case TIMER_SEC:
			MessageBeep(MB_OK);		//обработка одного сообщения в секунду 
			sweepAngle = sweepAngle + 6;
			if (sweepAngle == 360)sweepAngle = 0;
			label = (int)sweepAngle;
			InvalidateRect(hWnd, &rect, TRUE);
			break;
		}
		break;
	case WM_CLOSE:
		userReply = MessageBox(hWnd, TEXT("А вы уверены в своем желании закрыть приложение?"), TEXT(""),
			MB_YESNO | MB_ICONQUESTION);
		if (IDYES == userReply)
			DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hStart, hStop;

	switch (uMsg) {
	case WM_INITDIALOG:
		// Определяем дескрипторы элементов управления 
		hStart = GetDlgItem(hDlg, IDC_START);
		hStop = GetDlgItem(hDlg, IDC_STOP);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_START:
			EndDialog(hDlg, LOWORD(wParam));
			
			SendMessage(GetParent(hDlg), UM_START, 0, 0);
			break;
		case IDC_STOP:
			EndDialog(hDlg, LOWORD(wParam));

			SendMessage(GetParent(hDlg), UM_STOP, 0, 0);
			break;
		}
		break;
	}
	return FALSE;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
