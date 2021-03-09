#include "Submarine.h"

Submarine::Submarine()
{
	transform.scale = { 80, 20 };
	unitID = '3';
	detectShipDistance = 60;
	detectSubmersibleDistance = 80;
	life = 100;
	resource = 16;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = true;
	detectType[TYPE_AIRCRAFT] = false;
}

bool Submarine::CheckWeapon(string type)
{
	if (type == "Torpedo")
		return true;
	return false;
}

void Submarine::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("submarine_b.bmp") : TEXT("submarine_r.bmp"));
}