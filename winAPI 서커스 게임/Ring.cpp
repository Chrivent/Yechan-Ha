#include "Ring.h"

Ring::Ring()
{
	transform.position.y = 160;
	transform.scale = { 120, 320 };

	type = 0;
}

void Ring::Flaming()
{
	type += 1;

	if (type == 2)
		type = 0;
}

Collider Ring::GetCollider()
{
	Collider collider;
	collider.transform = transform;

	collider.transform.position.x += 50;
	collider.transform.scale.width -= 100;
	collider.transform.position.y += 290;
	collider.transform.scale.height -= 140;

	return collider;
}

Collider* Ring::GetScoreCollider()
{
	return NULL;
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

	//GetCollider().Draw(hdc);
}

Ring::~Ring()
{
}