#include "Aircraft.h"

Aircraft::Aircraft()
{
	type = "Aircraft";
}

void Aircraft::SetPositionOrigin()
{
	transform.position = { (color == BLACK) ? 0 - transform.scale.width : 1280, 180 - transform.scale.height };
}

bool Aircraft::CheckAntiWeapon(string type)
{
	if (type == "MachineGun_a" || type == "Shrapnel" || type == "Missile")
		return true;
	return false;
}