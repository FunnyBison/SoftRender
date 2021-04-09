#include "Render.h"
#include "VertexBreaker.h"
#include "common.h"
#include "Model.h"
#include <algorithm>
#include "Camera.h"

Render::Render()
{
}


Render::~Render()
{
}

void Render::Resize(HWND hwnd, int w, int h)
{
	m_bmp.DeleteBmp();
	m_bmp.Create(hwnd, w, h);
	m_width = w;
	m_height = h;

	g_Camera.ChangeAspect(1.0f * w / h);
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

	if (m_zBuffer.Set(i, j, v.pos.w)) {
		m_bmp.Set(i, j, RGB(R, G, B));
	}
}

void Render::Update(HDC hdc)
{
	g_model.UpdateFinal();
	m_zBuffer.Clean();
	m_bmp.Clean();

	for (auto pt : g_model.m_triangles) {
		FillTriangle(*pt);
	}

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
	else {
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

void Render::FillTriangle(const Triangle &t)
{
	Vertex v[3];
	for (int i = 0; i < 3; i++) {
		v[i] = g_model.GetVertex(t.vIndex[i]);
		g_model.TransformVertex(v[i]);
		ToScreen(v[i]);
	}

	std::sort(v, v+3, 
		[](const Vertex&v1, const Vertex&v2) {return v1.pos.y < v2.pos.y; });

	if (v[1].pos.y == v[0].pos.y) {
		FillPanTriangle(v[2], v[0], v[1]);
	}
	else if (v[1].pos.y == v[2].pos.y) {
		FillPanTriangle(v[0], v[2], v[1]);
	}
	else {
		VertexBreaker vb(v[0], v[2], (v[1].pos.y - v[0].pos.y) / (v[2].pos.y - v[0].pos.y));
		Vertex vInter;
		vb.Add();
		vb.GetPoint(vInter);
		FillPanTriangle(v[0], vInter, v[1]);
		FillPanTriangle(v[2], vInter, v[1]);
		Line(vInter, v[1]);
	}
}

void Render::FillPanTriangle(const Vertex & v0, const Vertex & v1, const Vertex & v2)
{
	int step = abs(v1.pos.y - v0.pos.y) + 1;
	float deltaY = v1.pos.y > v0.pos.y ? 1.0f : -1.0f;
	VertexBreaker vb1(v0, v1, deltaY / (v1.pos.y - v0.pos.y));
	VertexBreaker vb2(v0, v2, deltaY / (v2.pos.y - v0.pos.y));

	Vertex scan1, scan2;
	while (step > 0) {
		step--;
		vb1.GetPoint(scan1);
		vb2.GetPoint(scan2);
		//扫描线端点取整
		scan1.pos.x = round(scan1.pos.x);
		scan1.pos.y = round(scan1.pos.y);
		scan2.pos.x = round(scan2.pos.x);
		scan2.pos.y = round(scan2.pos.y);
		Line(scan1, scan2);
		vb1.Add();
		vb2.Add();
	}
}

void Render::ToScreen(Vertex & v)
{
	float x = v.pos.x / v.pos.w;
	float y = v.pos.y / v.pos.w;
	float z = v.pos.z / v.pos.w;

	x = m_width * (x + 1) * 0.5f;
	y = m_height * (y + 1) * 0.5f;

	v.pos.x = round(x);
	v.pos.y = round(y);
}
