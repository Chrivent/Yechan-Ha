#include "Corvette.h"

Corvette::Corvette()
{
	transform.scale = { 30, 10 };
	unitID = '1';
	detectShipDistance = 30;
	life = 40;
	resource = 7;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = false;
	detectType[TYPE_AIRCRAFT] = false;
}

bool Corvette::CheckWeapon(string type)
{
	if (type == "MachineGun_s")
		return true;
	return false;
}

void Corvette::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("corvette_b.bmp") : TEXT("corvette_r.bmp"));
}