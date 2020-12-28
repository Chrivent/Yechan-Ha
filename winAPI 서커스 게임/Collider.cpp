#include "Collider.h"

Collider::Collider()
{
}

void Collider::Draw(HDC hdc)
{
	DrawRectangleEmpty(hdc, transform, 3, RED);
}

Collider::~Collider()
{
}