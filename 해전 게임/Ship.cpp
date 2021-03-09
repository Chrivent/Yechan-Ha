#include "Ship.h"

Ship::Ship()
{
	type = "Ship";
}

void Ship::SetPositionOrigin()
{
	transform.position = { (color == BLACK) ? 0 - transform.scale.width : 1280, 360 - transform.scale.height };
}

bool Ship::CheckAntiWeapon(string type)
{
	if (type == "MachineGun_s" || type == "Torpedo" || type == "Missile")
		return true;
	return false;
}

void Ship::MoveUnit()
{
	if (target == NULL)
		(color == BLACK) ? transform.MoveRight() : transform.MoveLeft();
}