#include "Base.h"

void Base::SetPositionOrigin()
{
	transform.scale = { 70, 360 };
	transform.position = { (color == BLACK) ? 0 : 1280 - transform.scale.width, 180 };

	type = "Base";
	life = 8000;
}

bool Base::CheckWeapon(string type)
{
	return false;
}

bool Base::CheckAntiWeapon(string type)
{
	return true;
}

void Base::MoveUnit()
{

}

void Base::DrawUnit(HDC hdc)
{
	DrawRectangle(hdc, transform, color);
}