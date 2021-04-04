#pragma once
#include <Windows.h>
#include "MemBmp.h"
class Render
{
public:
	Render();
	~Render();

	void Resize(int w, int h);

	void Pixel(int x, int y, COLORREF clr);

	void Update(HDC hdc);

	MemBmp	m_bmp;
	//HDC		m_hDc;
	int m_width;
	int m_height;
};

