// MyDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


HHOOK hHook = NULL;
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == WM_LBUTTONDOWN)
	{
		// do nhấn chuột trái thì không làm gì nên mình sẽ trà về true đ
		return TRUE;
	}
	// nếu là những sự kiện khác thì tiếp tục chờ đợi để bắt hook
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}
void KhoiTaoHook(HWND hWnd)			//Dùng để khổi tạo thang hookk
{
	if (hHook != NULL) return;		// nếu nó đã có rồi thì không cần khởi toa nữa
	hHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseHookProc, 0, 0);	// khổi tạo hook
}
void HuyHook(HWND hWnd)			//Dùng để hủy hook
{
	if (hHook == NULL)	return;	//nếu không có giá trị thì bỏ qua
	UnhookWindowsHookEx(hHook);	// hủy hook
	hHook = NULL;
}