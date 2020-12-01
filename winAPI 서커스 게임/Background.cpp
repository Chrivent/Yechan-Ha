#include "Background.h"

Background::Background()
{
	type = 0;
	cheer = false;
}

void Background::PassingBackward()
{
	type++;

	if (type == 256)
		type = 0;
}

void Background::PassingForward()
{
	type--;

	if (type == -1)
		type = 255;
}

void Background::Cheering()
{
	cheer = (cheer == false) ? true : false;
}

void Background::Draw(HDC hdc)
{
	for (int i = 0; i < 16; i++)
	{
		if (i == 0 || i == 8)
			DrawBitmap(hdc, { { 160 * i - type * 5, 0 }, { 160, 160 } }, TEXT("back_deco.bmp"));
		else
		{
			if (cheer)
				DrawBitmap(hdc, { { 160 * i - type * 5, 0 }, { 160, 160 } }, TEXT("back_normal2.bmp"));
			else
				DrawBitmap(hdc, { { 160 * i - type * 5, 0 }, { 160, 160 } }, TEXT("back_normal.bmp"));
		}
	}

	DrawBitmap(hdc, { { 0, 160 }, { 1280, 560 } }, TEXT("back.bmp"));
}

Background::~Background()
{
}