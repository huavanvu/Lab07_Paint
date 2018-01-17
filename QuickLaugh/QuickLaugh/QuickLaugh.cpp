// QuickLaugh.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuickLaugh.h"
#include <shellapi.h>
#include <windowsx.h>
#include<iostream>
#include<vector>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <CommCtrl.h>
#pragma comment (lib, "Gdiplus.lib")
#pragma comment (lib, "Comctl32.lib")
using namespace Gdiplus;
using namespace std;
#define MAX_LOADSTRING 100
using namespace std;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Brush* bursh;
Brush* color[5];
Pen *pen;
Graphics *graphic;
Rect *elip;
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

	GdiplusStartupInput Input;
	ULONG_PTR Token;
	GdiplusStartup(&Token, &Input, NULL);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_QUICKLAUGH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUICKLAUGH));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUICKLAUGH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
	wcex.lpszMenuName = 0;
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
struct LinkData
{
	wstring filename;
	wstring path;
	int count = 0;
};
vector<LinkData> list;
vector<LinkData> listvectordata;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"Quick Launch", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, 1);
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

HHOOK hook;
HWND hwnd;
HWND combobox, listbox;
LRESULT CALLBACK HamXuLi(int message, WPARAM wParam, LPARAM lParam) 
{
	if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SPACE) & 1)) 
	{
		if (IsWindowVisible(hwnd) == false)
		{
			ShowWindow(hwnd,1);
		}
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		HWND focus = GetFocus();
		if (focus == listbox)
		{
			int pos = ListBox_GetCurSel(listbox);
			if (pos != -1)
			{
				ShellExecute(0, 0, listvectordata[pos].path.c_str(), 0, 0, 1);
				for (int i = 0; i < list.size(); i++)
				{
					if (listvectordata[pos].path== list[i].path)
					{
						list[i].count++;
						break;
					}
				}
			}
		}
	}
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN))
	{
		SetFocus(listbox);
	}
	return CallNextHookEx(hook, 0, 0, 0);
}
void LoadNotifyIcon(HWND hWnd)
{
	NOTIFYICONDATA notice = { 0 };
	notice.cbSize = sizeof(notice);
	notice.hWnd = hWnd;
	notice.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	notice.uCallbackMessage = 903;
	wcscpy_s(notice.szTip, 20 , L"Quick Lauch");
	notice.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));
	Shell_NotifyIcon(NIM_ADD, &notice);
}

void duyetFile(WCHAR* link)
{
	WCHAR linkfull[255];
	wsprintf(linkfull, L"%s\\*.*", link);
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(linkfull, &data);
	if ((int)h == -1)
	{
		return;
	}
	do
	{
		if (data.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)
		{
			if ((data.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN) == false)
				if (wcscmp(data.cFileName, L".") && wcscmp(data.cFileName, L".."))
				{
					WCHAR linkcon[255];
					wsprintf(linkcon, L"%s\\%s", link, data.cFileName);
					duyetFile(linkcon);
				}
		}
		else
		{
			if (wcsstr(data.cFileName, L"exe") != NULL)
			{
				LinkData dtl;
				dtl.filename = data.cFileName;
				dtl.path = link + wstring(L"\\") + data.cFileName;
				list.push_back(dtl);
			}
		}

	} while (FindNextFile(h, &data));
}
INT_PTR CALLBACK DrawChart(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	hwnd = hWnd;
    switch (message)
   {
	case WM_CREATE:
	{

		CreateWindow(L"static", L"Open : ", WS_CHILD | WS_VISIBLE, 200, 100, 50, 20, hwnd, 0, hInst, 0);
		CreateWindow(L"template", L"Demo", WS_CHILD | WS_VISIBLE, 200, 0, 100, 200, hwnd, 0, hInst, 0);
		combobox = CreateWindow(L"combobox", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 250, 100, 300, 300, hWnd, (HMENU)406, hInst, NULL);
		listbox = CreateWindow(L"listbox", L"", WS_CHILD | WS_VISIBLE | WS_BORDER|LBS_NOTIFY, 250, 125, 300, 300, hWnd, (HMENU)407, hInst, NULL);
		LoadNotifyIcon(hwnd);
		duyetFile(L"C:\\Program Files (x86)");
	//	hook = SetWindowsHookEx(WH_KEYBOARD_LL, HamXuLi, hInst, 0);
		ShowWindow(listbox, 0);
		break;
	}
	case 903:
		switch (lParam) 
		{
		case WM_LBUTTONUP:
		{
			if (IsWindowVisible(hWnd) == false)
			{
				ShowWindow(hwnd, 1);
			}
			
			break;
		}
			
		case WM_RBUTTONUP:
		{
			HMENU menu = CreatePopupMenu();
			AppendMenu(menu, MF_STRING, 667, L"View");
			AppendMenu(menu, MF_STRING, 668, L"Scan build database");
			AppendMenu(menu, MF_STRING, IDM_EXIT, L"Exit");
			POINT pos;
			GetCursorPos(&pos);
			TrackPopupMenu(menu, TPM_RIGHTBUTTON, pos.x, pos.y, 0, hwnd, NULL);
		}
			
		}
	

		break;
	
    case WM_COMMAND:
        {
			int wmEvent = HIWORD(wParam);
            int wmId = LOWORD(wParam);
			HWND combobox = (HWND)lParam;
            // Parse the menu selections:
            switch (wmId)
            {
			case 668:
			{
				duyetFile(L"C:\\Program Files (x86)");
				break;
			}
			case 667 :
			{
				DialogBox(hInst, MAKEINTRESOURCE(129), NULL, DrawChart);
				break;
			}
			case 406:
			{
				if (wmEvent == CBN_EDITCHANGE)
				{
					WCHAR ten[255];
					GetWindowText(combobox, ten, 255);
					for (int i = 0; i < listvectordata.size(); i++)
					{
						ListBox_DeleteString(listbox, 0);
					}
					listvectordata.clear();
					wstring tenkiemtra = ten;
					for (int i = 0; i < list.size(); i++)
					{
						if (list[i].filename.find(tenkiemtra) !=-1)
						{
							ListBox_AddString(listbox, list[i].filename.c_str());
							listvectordata.push_back(list[i]);
						}
					}
					ShowWindow(listbox, 1);
				}
				break;
			}
			case 407 :
			{
				if (wmEvent == LBN_DBLCLK)
				{
					int pos = ListBox_GetCurSel(listbox);
					if (pos == -1)
					{
						break;
					}
					ShellExecute(0, 0, listvectordata[pos].path.c_str(), 0, 0, 1);
					for (int i = 0; i < list.size(); i++)
					{
						if (listvectordata[pos].path == list[i].path)
						{
							list[i].count++;
							break;
						}
					}
				}
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
            // TODO: Add any drawing code that uses hdc here...
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
INT_PTR CALLBACK DrawChart(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	int wmID, wmEvent;
    switch (message)
    {
	case WM_PAINT :
	{
		vector<LinkData> componentlist;
		int sum = 0;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].count != 0)
			{
				componentlist.push_back(list[i]);
				sum += list[i].count;
			}
		}
		vector<float> percent;
		for (int i = 0; i < componentlist.size(); i++)
		{
			percent.push_back(((float)componentlist[i].count / sum) * 360);
		}
		
		float tam = 0;
		if (sum > 0)
		{
			float temp = 0;
			for (int i = 0; i < percent.size(); i++)
			{
				for (int j = i + 1; j < percent.size(); j++)
				{
					if (percent[i] < percent[j])
					{
						tam = percent[i];
						percent[i] = percent[j];
						percent[j] = tam;
					}
				}
			}
			color[0] = new SolidBrush(Color(255, 255, 0, 0));
			color[1] = new SolidBrush(Color(255, 255, 255, 0));
			color[2] = new SolidBrush(Color(255, 0, 255, 0));
			color[3] = new SolidBrush(Color(255, 0, 0, 255));
			color[4] = new SolidBrush(Color(255, 0, 0, 0));
			for (int i = 0; i < percent.size(); i++)
			{
				temp += percent[i];
			}
			HDC hdc = GetDC(hWnd);
			graphic = new Graphics(hdc);
			float start = 0;
			float end = 0;
			for (int i = 0; i < percent.size(); i++)
			{
				end = percent[i];
				graphic->FillPie(color[i], Rect(0, 0, 250, 250), start, end);
				start = start + end;
			}
		}

		break;
	}

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hWnd, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
INT_PTR CALLBACK About (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int wmID, wmEvent;
	switch (message)
	{
	case WM_PAINT:
	{
		break;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
