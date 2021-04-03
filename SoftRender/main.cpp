#include <Windows.h>  
#include "MainWindow.h"
#include <stdio.h>
#include "Matrix.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, char *, int cmdShow) {
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	AllocConsole();   

	
	freopen("CONOUT$", "w+t", stdout);    
	freopen("CONIN$", "r+t", stdin);  


	MainWindow mainWnd(hInstance, 800, 800, "Ö÷´°¿Ú");
	mainWnd.CreateTheWindow();
	MainWindow::WndMessageLoop();

	//int *p = new int();
	//*p = 3;
	return 0;
}
