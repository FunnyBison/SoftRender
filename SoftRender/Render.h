#pragma once
#include <Windows.h>
#include "MemBmp.h"
#include "GraphDef.h"
#include <array>
class Render
{
public:
	Render();
	~Render();

	void Resize(int w, int h);

	void Pixel(const Vertex &v);

	void Update(HDC hdc);

	void Line(const Vertex &v1, const Vertex& v2);

	void FillTriangle(const Triangle &t);

	void FillPanTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

	void ToScreen(Vertex &v);

	MemBmp	m_bmp;
	//HDC		m_hDc;
	int m_width;
	int m_height;
};
