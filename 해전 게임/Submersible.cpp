#include "Submersible.h"

Submersible::Submersible()
{
	type = "Submersible";
}

void Submersible::SetPositionOrigin()
{
	transform.position = { (color == BLACK) ? 0 - transform.scale.width : 1280, 450 - transform.scale.height };
}

bool Submersible::CheckAntiWeapon(string type)
{
	if (type == "DepthCharge" || type == "Torpedo")
		return true;
	return false;
}

void Submersible::MoveUnit()
{
	if (target == NULL)
		(color == BLACK) ? transform.MoveRight() : transform.MoveLeft();
}