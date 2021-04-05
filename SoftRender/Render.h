#pragma once
#include <Windows.h>
#include "MemBmp.h"
#include "GraphDef.h"
class Render
{
public:
	Render();
	~Render();

	void Resize(int w, int h);

	void Pixel(int x, int y, COLORREF clr);
	void Pixel(const Vertex &v);

	void Update(HDC hdc);

	void Line(const Vertex &v1, const Vertex& v2);

	MemBmp	m_bmp;
	//HDC		m_hDc;
	int m_width;
	int m_height;
};

