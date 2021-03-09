#include "MissileShell.h"

MissileShell::MissileShell(Unit* target)
{
	transform.scale = { 4, 10 };
	type = "Missile";
	damage = 5;

	this->target = target;
	mode = 1;
	moveCount = 0;
}

void MissileShell::Move()
{
	if (mode == 1)
	{
		int moveDistance = 5;
		transform.MoveUp(moveDistance);
		moveCount++;

		if (moveCount * moveDistance > 40)
		{
			int tmp = transform.scale.width;
			transform.scale.width = transform.scale.height;
			transform.scale.height = tmp;

			mode = 2;
		}
	}
	else
	{
		if (target == NULL)
			(color == BLACK) ? transform.MoveRight(6) : transform.MoveLeft(6);
		else
		{
			Position targetPosition;
			targetPosition.x = target->transform.position.x + target->transform.scale.width / 2;
			targetPosition.y = target->transform.position.y + target->transform.scale.height / 2;

			if (targetPosition.x > transform.position.x + 6)
				transform.MoveRight(6);
			else if (targetPosition.x < transform.position.x - 6)
				transform.MoveLeft(6);

			if (targetPosition.y > transform.position.y + 6)
				transform.MoveDown(6);
			else if (targetPosition.y < transform.position.y - 6)
				transform.MoveUp(6);
		}
	}
}

void MissileShell::Draw(HDC hdc)
{
	DrawRectangle(hdc, transform, color);
}