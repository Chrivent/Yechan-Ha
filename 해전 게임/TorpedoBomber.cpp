#include "TorpedoBomber.h"

TorpedoBomber::TorpedoBomber()
{
	transform.scale = { 40, 40 };
	unitID = '4';
	detectShipDistance = 40;
	detectSubmersibleDistance = 40;
	life = 100;
	resource = 14;

	detectType[TYPE_SHIP] = true;
	detectType[TYPE_SUBMERSIBLE] = true;
	detectType[TYPE_AIRCRAFT] = false;
}

bool TorpedoBomber::CheckWeapon(string type)
{
	if (type == "Torpedo")
		return true;
	return false;
}

void TorpedoBomber::DrawUnit(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (color == BLACK) ? TEXT("torpedo_bomber_b.bmp") : TEXT("torpedo_bomber_r.bmp"));
}

void TorpedoBomber::MoveUnit()
{
	if (target == NULL)
	{
		(color == BLACK) ? transform.MoveRight() : transform.MoveLeft();

		if (transform.position.y > 180 - transform.scale.height)
			transform.MoveUp();
		else if (transform.position.y < 180 - transform.scale.height)
			transform.MoveDown();
	}
	else
	{
		int thisX = transform.position.x;
		int targetX = target->transform.position.x;

		if (targetX > thisX)
		{
			if (targetX - thisX > 20)
				transform.MoveDown();

			if (targetX - thisX > 40)
				direction = "Right";
		}
		else
		{
			if (thisX - targetX > 20)
				transform.MoveUp();

			if (thisX - targetX > 40)
				direction = "Left";
		}

		(direction == "Right") ? transform.MoveRight() : transform.MoveLeft();
	}
}