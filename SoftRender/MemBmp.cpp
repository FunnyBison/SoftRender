#include "MemBmp.h"



MemBmp::MemBmp()
	: m_hBmp(NULL), m_hdcMem(NULL), m_bmpBuffer(nullptr)
{
}


MemBmp::~MemBmp()
{
	DeleteBmp();
}

void MemBmp::Create(HWND hwnd, int w, int h)
{
	m_bmpInfo.bmiHeader.biBitCount = 24;
	m_bmpInfo.bmiHeader.biSize = 40;
	m_bmpInfo.bmiHeader.biWidth = w;
	m_bmpInfo.bmiHeader.biHeight = h;
	m_bmpInfo.bmiHeader.biPlanes = 1;
	m_bmpInfo.bmiHeader.biCompression = 0;
	m_bmpInfo.bmiHeader.biSizeImage = (w * 24 + 31) / 32 * 4 * h;
	m_bmpInfo.bmiHeader.biXPelsPerMeter = 3780;
	m_bmpInfo.bmiHeader.biYPelsPerMeter = 3780;
	m_bmpInfo.bmiHeader.biClrUsed = 0;
	m_bmpInfo.bmiHeader.biClrImportant = 0;

	m_hBmp = CreateDIBSection(NULL, &m_bmpInfo, DIB_RGB_COLORS, &m_bmpBuffer, NULL, 0);
	m_hdcMem = CreateCompatibleDC(GetDC(hwnd));

	m_scanLineWidth = (m_bmpInfo.bmiHeader.biWidth * m_bmpInfo.bmiHeader.biBitCount / 8 + 3) / 4 * 4;
	m_clorByteNum = m_bmpInfo.bmiHeader.biBitCount / 8;
}

void MemBmp::Set(int x, int y, COLORREF c)
{
	BYTE *p = GetPointer(x, y);
	p[0] = GetBValue(c);
	p[1] = GetGValue(c);
	p[2] = GetRValue(c);
}

COLORREF MemBmp::Get(int x, int y)
{
	return COLORREF();
}

BYTE * MemBmp::GetPointer(int x, int y)
{
	BYTE *p = (BYTE*)m_bmpBuffer;
	return p + (y*m_scanLineWidth + x*m_clorByteNum);
}

void MemBmp::DeleteBmp()
{
	if (m_hBmp) {
		DeleteObject(m_hBmp);
		m_hBmp = NULL;
	}
	if (m_hdcMem) {
		DeleteObject(m_hdcMem);
		m_hdcMem = NULL;
	}
	m_bmpBuffer = NULL;
}

void MemBmp::Clean()
{
	ZeroMemory(m_bmpBuffer, m_bmpInfo.bmiHeader.biSizeImage);
}

void MemBmp::Draw(HDC hDc, int w, int h)
{
	HBITMAP oldBmp = (HBITMAP)SelectObject(m_hdcMem, m_hBmp);
	BitBlt(hDc, 0, 0, w, h, m_hdcMem, 0, 0, SRCCOPY);
	SelectObject(m_hdcMem, oldBmp);
}
