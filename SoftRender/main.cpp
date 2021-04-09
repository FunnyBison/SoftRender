#include <Windows.h>  
#include "MainWindow.h"
#include <stdio.h>
#include "Matrix.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Render.h"
class SoftRenderWindow : public MainWindow
{
	Render m_render;
public:
	SoftRenderWindow(HINSTANCE hIns, int w, int h, const char *name)
		:MainWindow(hIns, w, h, name) {}
	virtual LRESULT SelfWndProc (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)override
	{
		PAINTSTRUCT ps;
		HDC hdc;
		switch (msg){
		case WM_PAINT:
			hdc = BeginPaint(wnd, &ps);
			Paint(hdc);
			EndPaint(wnd, &ps);
			break;
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			m_render.Resize(width, height);
			break;
		}

		default:
			break;
		}
		return LRESULT();
	}

	void Paint(HDC hdc)
	{
		/*HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		Rectangle(hdc, 20, 20, 100, 100);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);*/
		m_render.Update(hdc);
	}
};

void Init();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, char *, int cmdShow) {
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	AllocConsole();   

	
	freopen("CONOUT$", "w+t", stdout);    
	freopen("CONIN$", "r+t", stdin);  

	Init();
	SoftRenderWindow mainWnd(hInstance, 805, 800, "Ö÷´°¿Ú");
	mainWnd.CreateTheWindow();
	SoftRenderWindow::WndMessageLoop();

	//int *p = new int();
	//*p = 3;
	return 0;
}
