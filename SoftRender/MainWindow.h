#pragma once
#include <Windows.h>
//���ڴ������ڣ���װһЩȫ�ֱ���
class MainWindow
{
public:
	//���캯����ָ��ʵ�������ڳߴ硢����
	MainWindow(HINSTANCE hIns, int w, int h, const char *name);
	virtual ~MainWindow();

	//�������ڣ�����Ҫ��������
	void CreateTheWindow();

	//������������Ϣ����
	virtual LRESULT SelfWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//������ѭ����ֱ�ӵ���
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
