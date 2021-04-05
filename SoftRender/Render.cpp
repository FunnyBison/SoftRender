#include "Render.h"
#include "VertexBreaker.h"
#include "common.h"

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

void Render::Pixel(const Vertex & v)
{
	int i = Round(v.pos.x);
	int j = Round(v.pos.y);
	int R = 255 * v.c.r;
	int G = 255 * v.c.g;
	int B = 255 * v.c.b;
	R = NUMMID(R, 0, 255);
	G = NUMMID(G, 0, 255);
	B = NUMMID(B, 0, 255);
	Pixel(i, j, RGB(R, G, B));
}

void Render::Update(HDC hdc)
{
	
	Vertex v1, v2;
	v1.pos.x = 0;
	v1.pos.y = 0;
	v1.pos.w = 0.5;

	v1.c.r = 1.0;
	v1.c.g = 0.5;
	v1.c.b = 0.0;

	v2.pos.x = 300;
	v2.pos.y = 450;
	v2.pos.w = 0.5;

	v2.c.r = 0.0;
	v2.c.g = 0.5;
	v2.c.b = 1.0;

	Line(v1, v2);

	m_bmp.Draw(hdc, m_width, m_height);
}

void Render::Line(const Vertex & v1, const Vertex & v2)
{
	int step;
	float fstep;

	int w = int(v2.pos.x - v1.pos.x);
	int h = int(v2.pos.y - v1.pos.y);
	if (abs(w) > abs(h)) {
		step = abs(w) + 1;
		float deltaX = (w > 0 ? 1.0f : -1);
		fstep = deltaX / (v2.pos.x - v1.pos.x);
	}
	else /*if (abs(h) > abs(w))*/ {
		step = abs(h) + 1;
		float deltaY = (h > 0 ? 1.0f : -1);
		fstep = deltaY / (v2.pos.y - v1.pos.y);
	}

	Vertex v;
	VertexBreaker vb(v1, v2, fstep);
	while (step > 0) {
		step--;
		vb.GetPoint(v);
		Pixel(v);
		vb.Add();
	}
}
