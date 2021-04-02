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

	Matrix m1(2, 3), m2(3, 2);
	m1.Init({ 1,2,3,4,5,6 });
	m2.Init({ 1,2,3,4,5,6 });
	m1.Print();
	m2.Print();
	Matrix m = Matrix::Product(m1, m2);
	m.Print();

	MainWindow mainWnd(hInstance, 800, 800, "������");
	mainWnd.CreateTheWindow();
	MainWindow::WndMessageLoop();
	//int *p = new int();
	//*p = 3;
	return 0;
}
