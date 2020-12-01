#include "Ring.h"

Ring::Ring()
{
	transform.position = { 1280, 180 };
	transform.scale = { 120, 320 };

	type = 0;
}

void Ring::Flaming()
{
	type = (type == 0) ? 1 : 0;
}

void Ring::FastMove()
{
	transform.position.x -= 6;
}

void Ring::SlowMove()
{
	transform.position.x -= 4;
}

void Ring::SlowestMove()
{
	transform.position.x -= 2;
}

void Ring::Draw(HDC hdc)
{
	Transform transform1 = transform;
	transform1.scale.width /= 2;

	DrawBitmapTransparent(hdc, transform1, (type == 0) ? TEXT("enemy_b.bmp") : TEXT("enemy_1b.bmp"));
}

void Ring::Draw2(HDC hdc)
{
	Transform transform2 = transform;
	transform2.position.x += transform.scale.width / 2;
	transform2.scale.width /= 2;

	DrawBitmapTransparent(hdc, transform2, (type == 0) ? TEXT("enemy_f.bmp") : TEXT("enemy_1f.bmp"));
}

Ring::~Ring()
{
}