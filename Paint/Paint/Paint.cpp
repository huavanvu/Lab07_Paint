// Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Paint.h"
#include <windowsx.h>
#include <vector>
#include <math.h>
#define MAX_LOADSTRING 100
using namespace std;
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
    LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

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
class Shape
{
protected:
	POINT start;
	POINT end;
public:
	Shape();
	virtual void Draw(HDC);
	~Shape();
};
class Line : public Shape
{
	
public:
	Line();
	Line(POINT, POINT);
	void Draw(HDC);
	~Line();
};

class Rectangles : public Shape
{
	
public:
	Rectangles();
	Rectangles(POINT, POINT);
	void Draw(HDC);
	~Rectangles();
};

class Ellipses : public Shape
{
	
public:
	Ellipses();
	Ellipses(POINT, POINT);
	void Draw(HDC);
	~Ellipses();
};
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAINT);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
void DrawSquare();
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
vector<Shape*> arrayshape;
bool mouseclick = false;
POINT startpoint;
POINT savepoint;
POINT endpoint;
Shape* object = NULL;
int shapetype = ID_DRAW_LINE;
POINT array_start_point[1000];
int numberstartpoint = 0;
POINT array_end_point[1000];
int numberendpoint = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_LBUTTONDOWN:
	{
		startpoint.x = GET_X_LPARAM(lParam);
		startpoint.y = GET_Y_LPARAM(lParam);
		array_start_point[numberstartpoint++] = startpoint;
		mouseclick = true;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (mouseclick == true)
		{
			savepoint.x = GET_X_LPARAM(lParam);
			savepoint.y = GET_Y_LPARAM(lParam);
			if (wParam&MK_SHIFT)
			{
				DrawSquare();
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		mouseclick = false;
		endpoint.x = GET_X_LPARAM(lParam);
		endpoint.y = GET_Y_LPARAM(lParam);
		if (wParam&MK_SHIFT)
		{
			DrawSquare();
		}
		array_end_point[numberendpoint++] = endpoint;
		arrayshape.push_back(object);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_DRAW_LINE:
			{
				shapetype = ID_DRAW_LINE;
				break;
			}
			case ID_DRAW_RECTANGLE:
			{
				shapetype = ID_DRAW_RECTANGLE;
				break;
			}
			case ID_DRAW_ELLIPSE:
			{
				shapetype = ID_DRAW_ELLIPSE;
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
			
			for (int i = 0; i < arrayshape.size(); i++)
			{
				arrayshape[i]->Draw(hdc);
			}
			if (mouseclick)
			{
				if (shapetype == ID_DRAW_LINE) 
				{
					object = new Line(startpoint, savepoint);
				}
				if (shapetype == ID_DRAW_RECTANGLE) 
				{
					object = new Rectangles(startpoint, savepoint);
				}
				if (shapetype == ID_DRAW_ELLIPSE)
				{
					object = new Ellipses(startpoint, savepoint);
				}
				object->Draw(hdc);
			}
            EndPaint(hWnd, &ps);
			break;
        }
        
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

Shape::Shape()
{

}

void Shape::Draw(HDC)
{
	
}

Shape::~Shape()
{
}

void Line::Draw(HDC hdc)
{
	MoveToEx(hdc, this->start.x, this->start.y, NULL);
	LineTo(hdc, this->end.x, this->end.y);
}
Line::~Line()
{
}
Line::Line()
{
}
Line::Line(POINT _start, POINT _end)
{
	this->start = _start;
	this->end = _end;
}
void Rectangles::Draw(HDC hdc)
{
	Rectangle(hdc, this->start.x, this->start.y, this->end.x, this->end.y);
}
Rectangles::~Rectangles()
{
}
Rectangles::Rectangles()
{
}
Rectangles::Rectangles(POINT _start, POINT _end)
{
	this->start = _start;
	this->end = _end;
}
void Ellipses::Draw(HDC hdc)
{
	Ellipse(hdc, this->start.x, this->start.y, this->end.x, this->end.y);
}

Ellipses::~Ellipses()
{
}

Ellipses::Ellipses()
{
}

Ellipses::Ellipses(POINT _start, POINT _end)
{
	this->start = _start;
	this->end = _end;
}

void DrawSquare()
{
	if (abs(startpoint.x - savepoint.x) > abs(startpoint.y - savepoint.y))
	{
		if (startpoint.x > savepoint.x)
		{
			savepoint.x = startpoint.x - abs(startpoint.y - savepoint.y);
		}
		else
		{
			savepoint.x = startpoint.x + abs(startpoint.y - savepoint.y);
		}
	}
	else
	{
		if (startpoint.y > savepoint.y)
		{
			savepoint.y = startpoint.y - abs(startpoint.x - savepoint.x);
		}
		else
		{
			savepoint.y = startpoint.y + abs(startpoint.x - savepoint.x);
		}
	}
}
