#pragma once
#include <Windows.h>
class MemBmp
{
public:
	MemBmp();
	~MemBmp();

	void Create(int w, int h);

	void Set(int x, int y, COLORREF c);

	COLORREF Get(int x, int y);

	BYTE *GetPointer(int x, int y);

	void DeleteBmp();

	void Clean();

	void Draw(HDC hDc, int w, int h);

private:
	HBITMAP m_hBmp;
	BITMAPINFO m_bmpInfo;

	void *	m_bmpBuffer;
	
	int m_scanLineWidth;
	int m_clorByteNum;
};

