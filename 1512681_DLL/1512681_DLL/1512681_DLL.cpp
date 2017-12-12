// 1512517_GDIPlus.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512681_DLL.h"
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include <vector>
#include "Shapes.h"
#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;
HWND hWnd;// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

												// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return FALSE;
	}

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY1512517_GDIPLUS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512517_GDIPLUS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CoUninitialize();
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;//CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1512517_GDIPLUS));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY1512517_GDIPLUS);
	wcex.lpszClassName = L"Ten";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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

	hWnd = CreateWindow(L"Ten", L"Paint", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

vector<Shape*> dsHinhVe;
vector<Shape*> Prototype;
Shape* reShape;
Shape* shape;

ShapeFactory shapeFactor;

void DieuChinh(POINT &pDieuChinh);
bool shiftDown = false;
bool onPress = false;
int Type;
RECT rect;


POINT bd;
POINT kt;
POINT pDiChuyen;

int size = 2;
Color color = Color(255, 0, 0, 0);

GdiplusStartupInput gdiPlusStartupInput;
ULONG_PTR gdiPlusToken;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
		InitializeFramework(hWnd);
		GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, NULL);

		Prototype.push_back(new CLine());
		Prototype.push_back(new CRectangle());
		Prototype.push_back(new CEllipse());
		Type = TY_LINE;
		reShape = Prototype[0];
	}
	break;
	case WM_LBUTTONDOWN:
	{
		onPress = true;
		bd.x = GET_X_LPARAM(lParam);
		bd.y = GET_Y_LPARAM(lParam);
		SetCapture(hWnd);
	}
	break;
	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		onPress = false;
		kt.x = GET_X_LPARAM(lParam);
		kt.y = GET_Y_LPARAM(lParam);
		shape = shapeFactor.getShape(Type);
		if (shiftDown == true) {
			DieuChinh(kt);
			shiftDown = false;
		}
		shape->setPoint(bd, kt);
		dsHinhVe.push_back(shape);
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (onPress == true) {
			pDiChuyen.x = GET_X_LPARAM(lParam);
			pDiChuyen.y = GET_Y_LPARAM(lParam);
			if (wParam & MK_SHIFT) {
				DieuChinh(pDiChuyen);
				shiftDown = true;
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
	}
	break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_BTN_NEW:
		{
			dsHinhVe.clear();
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
		case ID_SHAPE_ELIPSE:
		{
			Type = TY_ELLIPSE;
			reShape = Prototype[2];
		}
		break;
		case ID_SHAPE_LINE:
		{
			Type = TY_LINE;
			reShape = Prototype[0];
		}
		break;
		case ID_SHAPE_RECTANGLE:
		{
			Type = TY_RECTANGLE;
			reShape = Prototype[1];
		}
		break;
		case ID_BTN_EXIT:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		HDC hdcTam = CreateCompatibleDC(hdc);
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		SelectObject(hdcTam, bitmap);
		FillRect(hdcTam, &rect, (HBRUSH)(COLOR_WINDOW + 1));
		SelectObject(hdcTam, GetStockObject(NULL_BRUSH));
		Graphics* gp = new Graphics(hdcTam);
		Pen* pen = new Pen(color, 2);

		for (int i = 0; i < dsHinhVe.size(); i++) {
			dsHinhVe[i]->Draw(gp, pen);
		}

		if (onPress == true) {
			reShape->setPoint(bd, pDiChuyen);
			reShape->Draw(gp, pen);
		}

		int ribbonHeight = GetRibbonHeight();
		BitBlt(hdc, 0, ribbonHeight, rect.right, rect.bottom, hdcTam, 0, ribbonHeight, SRCCOPY);


		delete pen;
		delete gp;
		DeleteBitmap(bitmap);
		DeleteDC(hdcTam);
		DeleteDC(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		GdiplusShutdown(gdiPlusToken);
		//DestroyFramework();
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

void DieuChinh(POINT &pDieuChinh) {
	if (abs(pDieuChinh.x - bd.x) > abs(pDieuChinh.y - bd.y))
	{
		if (bd.y < pDieuChinh.y)
			pDieuChinh.y = bd.y + abs(pDieuChinh.x - bd.x);
		else
			pDieuChinh.y = bd.y - abs(pDieuChinh.x - bd.x);
	}
	else {
		if (bd.x < pDieuChinh.x) {
			pDieuChinh.x = bd.x + abs(pDieuChinh.y - bd.y);
		}
		else
			pDieuChinh.x = bd.x - abs(pDieuChinh.y - bd.y);
	}
}