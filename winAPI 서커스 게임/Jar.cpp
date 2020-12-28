#include "Jar.h"

Jar::Jar()
{
	transform.position.y = 500;
	transform.scale = { 130, 130 };

	type = 0;
}

void Jar::Flaming()
{
	type += 1;

	if (type == 2)
		type = 0;
}

Collider Jar::GetCollider()
{
	Collider collider;
	collider.transform = transform;

	collider.transform.position.x += 40;
	collider.transform.scale.width -= 80;

	return collider;
}

void Jar::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (type == 0) ? TEXT("front.bmp") : TEXT("front2.bmp"));

	//GetCollider().Draw(hdc);
}

Jar::~Jar()
{
}