#include "Helicopter.h"

Helicopter::Helicopter()
{
	transform.scale = { 60, 20 };
	unitID = '5';
	detectShipDistance = 60;
	detectAircraftDistance = 60;
	life = 80;
	resource = 16;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = false;
	detectType[TYPE_AIRCRAFT] = true;
}

bool Helicopter::CheckWeapon(string type)
{
	if (type == "MachineGun_s" || type == "MachineGun_a")
		return true;
	return false;
}

void Helicopter::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("helicopter_b.bmp") : TEXT("helicopter_r.bmp"));
}

void Helicopter::MoveUnit()
{
	if (target == NULL)
	{
		(color == BLACK) ? transform.MoveRight() : transform.MoveLeft();

		if (transform.position.y > 180 - transform.scale.height + 40)
			transform.MoveUp();
		else if (transform.position.y < 180 - transform.scale.height - 40)
			transform.MoveDown();
	}
	else
	{
		Position targetPosition = target->transform.position;
		targetPosition.x = target->transform.position.x + target->transform.scale.width / 2;
		targetPosition.y = target->transform.position.y;

		if (targetPosition.x > transform.position.x + 40)
			transform.MoveRight();
		else if (targetPosition.x < transform.position.x - 40)
			transform.MoveLeft();

		if (targetPosition.y > transform.position.y + 40)
			transform.MoveDown();
		else if (targetPosition.y < transform.position.y - 40)
			transform.MoveUp();
	}
}