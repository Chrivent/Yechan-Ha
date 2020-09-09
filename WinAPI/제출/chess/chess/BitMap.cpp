#include "BitMap.h"

BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc, LPCWSTR FileName)
{
	m_MemDC = CreateCompatibleDC(hdc);

	m_MyBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_MyBitmap);
	BITMAP BitMap_Info;
	GetObject(m_MyBitmap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;

}

void BitMap::Draw(HDC hdc, int x, int y, float bx, float by)	//x, y : 그릴 위치 bx, by:그릴 사이즈
{
	TransparentBlt(hdc, x, y, bx, by, m_MemDC, 0, 0, bx, by, RGB(255, 0, 255));
}

BitMap::~BitMap()
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_MyBitmap);
	DeleteDC(m_MemDC);
}
