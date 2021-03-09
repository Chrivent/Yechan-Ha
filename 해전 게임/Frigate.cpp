#include "Frigate.h"

Frigate::Frigate()
{
	transform.scale = { 80, 20 };
	unitID = '2';
	detectShipDistance = 60;
	detectSubmersibleDistance = -40;
	life = 100;
	resource = 20;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = true;
	detectType[TYPE_AIRCRAFT] = false;
}

bool Frigate::CheckWeapon(string type)
{
	if (type == "MachineGun_s" || type == "DepthCharge")
		return true;
	return false;
}

void Frigate::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("frigate_b.bmp") : TEXT("frigate_r.bmp"));
}