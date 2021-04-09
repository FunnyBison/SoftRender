#include "MainWindow.h"
#include <stdio.h>


MainWindow::MainWindow(HINSTANCE hIns, int w, int h, const char *name)
{
	m_hInstance = hIns;
	m_hWnd = NULL;
	m_width = w;
	m_height = h;
	strcpy(m_wndName, name);
	m_wndProc = MainWindow::DefaultProc;
}

MainWindow::~MainWindow()
{
}

void MainWindow::MoveCenter()
{
	int w = m_width;
	int h = m_height;
	int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
	MoveWindow(m_hWnd, x, y, w, h, FALSE);
}

void MainWindow::RegisterClass()
{
	GenClassName();

	WNDCLASSEX  wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.style = CS_VREDRAW | CS_HREDRAW;
	wce.lpfnWndProc = m_wndProc;  //指明回调函数  
	wce.hInstance = GetModuleHandle(0);
	wce.hIcon = LoadIcon(0, IDI_WINLOGO);
	wce.hCursor = LoadCursor(0, IDC_ARROW);
	wce.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);;
	wce.lpszClassName = m_className; //独一无二的类名  
	wce.hIconSm = wce.hIcon;
	RegisterClassEx(&wce);
}

void MainWindow::CreateTheWindow()
{
	RegisterClass();
	m_hWnd = CreateWindowEx(0, m_className, m_wndName, WS_OVERLAPPEDWINDOW,
		0, 0, m_width, m_height,
		NULL, NULL, m_hInstance, NULL);

	SetWindowLong(m_hWnd, GWL_USERDATA, LONG(this));
	MoveCenter();

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

LRESULT MainWindow::DefaultProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MainWindow *pWnd = (MainWindow*)GetWindowLong(wnd, GWL_USERDATA);
	if (pWnd != NULL) {
		if (!pWnd->SelfWndProc(wnd, msg, wParam, lParam)) {
			return 0;
		}
	}

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0); //如果是“窗口销毁”事件，则应该在消息队列中投递  
		break;              //一个WM_QUIT消息，使GetMessage()返回FALSE  
	default:
		return DefWindowProc(wnd, msg, wParam, lParam);
	}
	return 0;
}

DWORD MainWindow::WndMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

void MainWindow::GenClassName()
{
	strcpy(m_className, "MY_WND_CLASS");

	char time[20];
	DWORD tc = GetTickCount();
	sprintf(time, "%u", tc);
	strcat(m_className, time);
}
