#include "Destroyer.h"

Destroyer::Destroyer()
{
	transform.scale = { 100, 30 };
	unitID = '6';
	detectShipDistance = 80;
	detectAircraftDistance = 60;
	life = 140;
	resource = 22;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = false;
	detectType[TYPE_AIRCRAFT] = true;
}

bool Destroyer::CheckWeapon(string type)
{
	if (type == "MachineGun_s" || type == "Shrapnel")
		return true;
	return false;
}

void Destroyer::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("destroyer_b.bmp") : TEXT("destroyer_r.bmp"));
}