#include "ShrapnelShell.h"

ShrapnelShell::ShrapnelShell(Position targetPosition, float angle, float angle2)
{
	transform.scale = { 3, 3 };
	type = "Shrapnel";
	damage = 5;

	this->targetPosition = targetPosition;
	this->angle = angle;
	this->angle2 = angle2;

	explode = false;
	moveCount = 0;
}

void ShrapnelShell::Move()
{
	int range = 120;
	Transform tmp;
	tmp.position = { targetPosition.x - range / 2, targetPosition.y - range / 2 };
	tmp.scale = { range, range };

	if (CheckTransformIsIntersect(transform, tmp))
		explode = true;

	if (explode == false)
		transform.position = AnglePosition(transform.position, 4, angle);
	else
	{
		int moveDistance = 7;

		transform.position = AnglePosition(transform.position, moveDistance, angle2);
		moveCount++;

		if (transform.position.y > 360 || moveCount * moveDistance > 100)
			breakaway = true;
	}
}

void ShrapnelShell::Draw(HDC hdc)
{
	DrawEllipse(hdc, transform, color);
}