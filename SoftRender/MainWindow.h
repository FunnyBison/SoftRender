#pragma once
#include <Windows.h>
//用于创建窗口，封装一些全局变量
class MainWindow
{
public:
	//构造函数，指定实例、窗口尺寸、名字
	MainWindow(HINSTANCE hIns, int w, int h, const char *name);
	virtual ~MainWindow();

	//创建窗口，不需要其他参数
	void CreateTheWindow();

	//用于重载做消息处理
	virtual LRESULT SelfWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//窗口主循环，直接调用
	static DWORD WndMessageLoop();
private:
	static LRESULT CALLBACK DefaultProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void GenClassName();
	void MoveCenter();
	void RegisterClass();
private:
	char	m_className[128];
	char	m_wndName[128];

	HINSTANCE	m_hInstance;
	HWND	m_hWnd;
	WNDPROC	m_wndProc;

	int		m_width;
	int		m_height;
};
