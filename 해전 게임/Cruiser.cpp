#include "Cruiser.h"

Cruiser::Cruiser()
{
	transform.scale = { 120, 40 };
	unitID = '7';
	detectShipDistance = 300;
	detectAircraftDistance = 300;
	life = 160;
	resource = 24;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = false;
	detectType[TYPE_AIRCRAFT] = true;
}

bool Cruiser::CheckWeapon(string type)
{
	if (type == "Missile")
		return true;
	return false;
}

void Cruiser::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("cruiser_b.bmp") : TEXT("cruiser_r.bmp"));
}