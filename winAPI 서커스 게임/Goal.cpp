#include "Goal.h"

Goal::Goal()
{
	transform.position = { 12800, 500 };
	transform.scale = { 200, 130 };
}

Collider Goal::GetCollider()
{
	Collider collider;
	collider.transform = transform;

	collider.transform.position.x -= 20;
	collider.transform.position.y += 20;
	collider.transform.scale.width += 40;
	collider.transform.scale.height -= 110;

	return collider;
}

void Goal::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, TEXT("end.bmp"));

	//GetCollider().Draw(hdc);
}

Goal::~Goal()
{
}