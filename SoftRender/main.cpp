#include <Windows.h>  
#include "MainWindow.h"
#include <stdio.h>
#include "Matrix.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Render.h"
#include "Model.h"
#include "common.h"
Render g_render;
class SoftRenderWindow : public MainWindow
{
public:
	SoftRenderWindow(HINSTANCE hIns, int w, int h, const char *name)
		:MainWindow(hIns, w, h, name) {}
	virtual LRESULT SelfWndProc (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)override
	{
		switch (msg){
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			g_render.Resize(m_hWnd, width, height);
			break;
		}
		case WM_ERASEBKGND:
			return 0;
			break;

		default:
			break;
		}
		return 1;
	}

	DWORD GameLoop()
	{
		const int FRAMES_PER_SECOND = 25;
		const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
		DWORD next_game_tick = GetTickCount(); // 返回当前的系统已经运行的毫秒数
		int sleep_time = 0;
		bool game_is_running = true;
		
		MSG msg = {};
		while( game_is_running )
		{
			//update_game();
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				g_model.m_world.RotateY(DToR(4)).RotateX(DToR(2)).RotateZ(DToR(3));
				g_render.Update(GetDC(m_hWnd));

				next_game_tick += SKIP_TICKS;
				sleep_time = next_game_tick - GetTickCount();
				if (sleep_time >= 0)
				{
					Sleep(sleep_time);
				}
			}
		}

		return 1;
	}
};

void Init();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, char *, int cmdShow) {
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	AllocConsole();   

	
	freopen("CONOUT$", "w+t", stdout);    
	freopen("CONIN$", "r+t", stdin);  

	Init();
	SoftRenderWindow mainWnd(hInstance, 805, 800, "主窗口");
	mainWnd.CreateTheWindow();
	mainWnd.GameLoop();

	//int *p = new int();
	//*p = 3;
	return 0;
}
