#include "TorpedoShell.h"

TorpedoShell::TorpedoShell(Unit* target)
{
	transform.scale = { 8, 2 };
	type = "Torpedo";
	damage = 6;

	this->target = target;
}

void TorpedoShell::Move()
{
	if (transform.position.y < 360)
		transform.MoveDown(3);
	else
	{
		if (target == NULL)
			(color == BLACK) ? transform.MoveRight(2) : transform.MoveLeft(2);
		else
		{
			Position targetPosition;
			targetPosition.x = target->transform.position.x + target->transform.scale.width / 2;
			targetPosition.y = target->transform.position.y + target->transform.scale.height / 2;

			if (targetPosition.x > transform.position.x + 2)
				transform.MoveRight(2);
			else if (targetPosition.x < transform.position.x - 2)
				transform.MoveLeft(2);

			if (targetPosition.y > transform.position.y + 2)
				transform.MoveDown(2);
			else if (targetPosition.y < transform.position.y - 2)
				transform.MoveUp(2);
		}
	}
}

void TorpedoShell::Draw(HDC hdc)
{
	Position position2 = { transform.position.x + transform.scale.width, transform.position.y };

	DrawLine(hdc, transform.position, position2, transform.scale.height, color);
}