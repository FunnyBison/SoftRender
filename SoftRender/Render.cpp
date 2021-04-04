#include "Render.h"



Render::Render()
{
}


Render::~Render()
{
}

void Render::Resize(int w, int h)
{
	m_bmp.DeleteBmp();
	m_bmp.Create(w, h);
	m_width = w;
	m_height = h;
}

void Render::Pixel(int x, int y, COLORREF clr)
{
	m_bmp.Set(x, y, clr);
}

void Render::Update(HDC hdc)
{
	for (int i = 0; i < 100; i++) {
		Pixel(i, 10, RGB(255, 0, 0));
	}

	m_bmp.Draw(hdc, m_width, m_height);
}
