// Midterm.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Midterm.h"
#include <string>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <CommCtrl.h>
#define MAX_LOADSTRING 100
using namespace std;
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MIDTERM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIDTERM));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIDTERM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MIDTERM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd;
   hWnd = CreateWindowEx(0, szWindowClass, L"Quản lý chi tiêu",
	   WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, 900, 700, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
HWND Type;
HWND Data;
HWND Money;
HWND Total;
HWND Sum;
WCHAR temp1 [255];
WCHAR temp2 [255];
WCHAR temp3 [255];
int chart[6] = { 0 };
int status = 0;
HWND report;
fstream in, out;
void WriteData();
void Convert1(string str, LPWSTR str1);
void Convert2(char* str, LPWSTR str1);
void ReadData();
void ListViewData();
int sumall = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		LOGFONT lf;
		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
		HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
			lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
			lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
			lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
			lf.lfPitchAndFamily, lf.lfFaceName);
		//CreateWindow(WC_LISTVIEWW, L"",
			//WS_CHILD | WS_VISIBLE |
			//WS_VSCROLL | LVS_REPORT | WS_BORDER,
			//200, 10, 200, 400,
			//hWnd, (HMENU)IDC_LISTVIEW, hInst, NULL);

		CreateWindow(L"static", L"Thêm một loại chi tiêu", WS_CHILD | WS_VISIBLE, 50, 0, 150, 20, hWnd, 0, hInst, 0);
		Type = CreateWindow(L"combobox", L"", WS_CHILD | WS_VISIBLE|CBS_DROPDOWN, 70, 60, 150, 1000, hWnd, 0, hInst, 0);
		CreateWindow(L"static", L"Loại chi tiêu :", WS_CHILD | WS_VISIBLE, 70, 30, 100, 20, hWnd, 0, hInst, 0);
		CreateWindow(L"static", L"Nội dung", WS_CHILD | WS_VISIBLE, 300, 30, 60, 20, hWnd, 0, hInst, 0);
		CreateWindow(L"static", L"Số tiền: ", WS_CHILD | WS_VISIBLE, 500, 30, 50, 20, hWnd, 0, hInst, 0);
		Data = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE, 300, 60, 150, 20, hWnd, 0, hInst, 0);
		Money = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER, 500, 60, 150, 20, hWnd, 0, hInst, 0);
		CreateWindow(L"static", L"Toàn bộ danh sách các chi tiêu", WS_CHILD | WS_VISIBLE, 50, 130, 300, 20, hWnd, 0, hInst, 0);
		report = CreateWindow(WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LVS_REPORT, 70, 170, 700, 200, hWnd, 0, hInst, 0);
		CreateWindow(L"static", L"Thông tin thống kê", WS_CHILD | WS_VISIBLE, 50, 400, 300, 20, hWnd, 0, hInst, 0);
		CreateWindow(L"static", L"Tổng cộng :", WS_CHILD | WS_VISIBLE, 300, 430, 300, 20, hWnd, 0, hInst, 0);
		Sum = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE|ES_READONLY, 400, 430, 150, 20, hWnd, 0, hInst, 0);
		//report = CreateWindow(WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LVS_REPORT, 70, 170, 700, 200, hWnd, 0, hInst, 0);
		CreateWindow(L"button", L"Thêm", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 60, 100, 25, hWnd, (HMENU)1024, hInst, 0);
		ComboBox_AddString(Type, L"An uong");
		ComboBox_AddString(Type, L"Di chuyen");
		ComboBox_AddString(Type, L"Nha cua");
		ComboBox_AddString(Type, L"Xe co");
		ComboBox_AddString(Type, L"Nhu yeu pham");
		ComboBox_AddString(Type, L"Dich vu");
		ListViewData();
		ListView_SetExtendedListViewStyle(report, LVS_EX_FULLROWSELECT | LVS_EX_JUSTIFYCOLUMNS | LVS_EX_UNDERLINEHOT | LVS_EX_GRIDLINES);
		ReadData();
		WCHAR Sumall[255];
		_itow(sumall, Sumall, 10);
		SetWindowText(Sum, Sumall);
		out.open("Input.txt", ios::out | ios::app);
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case 1024:
			{
				GetWindowText(Type, temp1, 255);
				GetWindowText(Data, temp2, 255);
				GetWindowText(Money, temp3, 255);
				LVITEM list;
				list.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
				list.iSubItem = 0;
				list.pszText = temp1;
				list.iItem = status;
				list.cchTextMax = 2;
				ListView_InsertItem(report, &list);
				ListView_SetItemText(report, status, 0, temp1);
				ListView_SetItemText(report, status, 1, temp2);
				ListView_SetItemText(report, status, 2, temp3);
				status++;
				WriteData();

				if (wcscmp(temp1, L"An uong") == 0)
				{
					chart[0] += _wtoi(temp3);
				}
				if (wcscmp(temp1, L"Di chuyen") == 0)
				{
					chart[1] += _wtoi(temp3);
				}
				if (wcscmp(temp1, L"Nha cua") == 0)
				{
					chart[2] += _wtoi(temp3);
				}
				if (wcscmp(temp1, L"Xe co") == 0)
				{
					chart[3] += _wtoi(temp3);
				}
				if (wcscmp(temp1, L"Nhu yeu pham") == 0)
				{
					chart[4] += _wtoi(temp3);
				}
				if (wcscmp(temp1,L"Dich vu")==0)
				{
					chart[5] += _wtoi(temp3);
				}
				sumall += _wtoi(temp3);
				
				WCHAR Sumall[255];
				_itow(sumall, Sumall, 10);
				SetWindowText(Sum, Sumall);

				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

			RECT rect;
			rect.left = 50;
			rect.top = 0;
			rect.bottom = 0;
			rect.right = 50;
			int Size = 0;
			HBRUSH hbr[6];
			hbr[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbr[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbr[2] = CreateSolidBrush(RGB(255, 0, 255));
			hbr[3] = CreateSolidBrush(RGB(0, 0, 255));
			hbr[4] = CreateSolidBrush(RGB(0, 255, 0));
			hbr[5] = CreateSolidBrush(RGB(0, 255, 255));
			
			for (int i = 0; i < 6; i++)
			{
				rect.left += Size;
				rect.top = 500;
				rect.bottom = 530;
				int t;
				if (sumall == 0) {
					 t = 16;
				}else	
				 t = chart[i] * 100 / sumall;
				Size = t * 8;
				rect.right += Size;
				FillRect(hdc, &rect, hbr[i]);
			}
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
void WriteData()
{
	char tmp1[255], tmp2[255], tmp3[255];
	Convert2(tmp1, temp1);
	Convert2(tmp2, temp2);
	Convert2(tmp3, temp3);
	out << endl << tmp1 << endl << tmp2 << endl << tmp3;
}
void Convert1(string str, LPWSTR str1)
{
	int n = str.length();
	for (int i = 0; i < n; i++)
	{
		str1[i] = str[i];
	}
	str1[n] = '\0';
}
void Convert2(char* str, LPWSTR str1)
{
	int i = 0;
	while (str1[i] != 0)
	{
		str[i] = str1[i];
		i++;
	}
	str[i] = '\0';
}
void ReadData()
{
	string tmp1, tmp2, tmp3;
	char data;
	in.open("Input.txt", ios::in);
	in.ignore();
	while (!in.eof())
	{
		getline(in, tmp1);
		getline(in, tmp2);
		getline(in, tmp3);
		if (tmp1 == "An uong")
		{
			chart[0] += atoi(tmp3.c_str());
		}
		if (tmp1 == "Di chuyen")
		{
			chart[1] += atoi(tmp3.c_str());
		}
		if (tmp1 == "Nha cua")
		{
			chart[2] += atoi(tmp3.c_str());
		}
		if (tmp1 == "Xe co")
		{
			chart[3] += atoi(tmp3.c_str());
		}
		if (tmp1 == "Nhu yeu pham")
		{
			chart[4] += atoi(tmp3.c_str());
		}
		if (tmp1 == "Dich vu")
		{
			chart[5] += atoi(tmp3.c_str());
		}

		WCHAR temp1[255], temp2[255], temp3[255];
		Convert1(tmp1, temp1);
		Convert1(tmp2, temp2);
		Convert1(tmp3, temp3);

		sumall+=_wtoi(temp3);

		LVITEM list;
		list.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		list.iSubItem = 0;
		list.pszText = temp1;
		list.iItem = status;
		list.cchTextMax = 2;
		ListView_InsertItem(report, &list);
		ListView_SetItemText(report, status, 0, temp1);
		ListView_SetItemText(report, status, 1, temp2);
		ListView_SetItemText(report, status, 2, temp3);
		status++;
	}
	in.close();
}
void ListViewData()
{
	LVCOLUMN column;
	column.cx = 100;
	column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	column.fmt = LVCFMT_LEFT;
	column.pszText = L"Loại chi tiêu";
	ListView_InsertColumn(report, 0, &column);
	column.cx = 180;
	column.pszText = L"Nội dung";
	ListView_InsertColumn(report, 1, &column);
	column.cx = 100;
	column.pszText = L"Số tiền";
	ListView_InsertColumn(report, 2, &column);
}
//Severity	Code	Description	Project	File	Line	Suppression State
//Error	C4996	'_itow': This function or variable may be unsafe.Consider using _itow_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.Midterm	c : \users\admin\onedrive\visual studio\midterm\midterm\midterm.cpp	189
