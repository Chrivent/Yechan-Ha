#pragma once
#include "define.h"

class BitMap
{
private:
	HDC m_MemDC;
	HBITMAP m_MyBitmap;
	HBITMAP m_OldBitmap;
	SIZE m_size;
public:
	void Init(HDC hdc, LPCWSTR FileName);
	void Draw(HDC hdc, int x, int y, float spX, float spY);
	inline SIZE GetSize()
	{
		return m_size;
	}
	BitMap();
	~BitMap();
};

