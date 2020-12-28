#include "Background.h"

Background::Background()
{
	transform.position = { 0, 0 };

	type = 0;
}

void Background::Cheering()
{
	type += 1;

	if (type == 2)
		type = 0;
}

void Background::Draw(HDC hdc)
{
	for (int j = 0; j < 11; j++)
	{
		DrawBitmap(hdc, { { transform.position.x + j * 1280, 0 }, { 160, 160 } }, TEXT("back_deco.bmp"));

		for (int i = 0; i < 7; i++)
			DrawBitmap(hdc, { { transform.position.x + j * 1280 + i * 160 + 160, 0 }, { 160, 160 } }, (type == 0) ? TEXT("back_normal.bmp") : TEXT("back_normal2.bmp"));

		DrawBitmap(hdc, { { transform.position.x + j * 1280, 640 }, { 240, 80 } }, TEXT("miter.bmp"));

		TCHAR distance[512];
		wsprintf(distance, TEXT("%d"), 100 - j * 10);

		DrawTextOut(hdc, { { transform.position.x + j * 1280 + 20, 660 }, { 120, 40 } }, distance, WHITE);
	}

	DrawBitmap(hdc, { { transform.position.x, 160 }, { 14080, 480 } }, TEXT("back.bmp"));
}

Background::~Background()
{
}