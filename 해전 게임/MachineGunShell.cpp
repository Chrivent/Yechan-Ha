#include "MachineGunShell.h"

MachineGunShell::MachineGunShell(float angle, string type)
{
	transform.scale = { 4, 4 };
	this->type = type;
	damage = 2;

	this->angle = angle;
	moveCount = 0;
}

void MachineGunShell::Move()
{
	int moveDistance = 10;

	transform.position = AnglePosition(transform.position, moveDistance, angle);
	moveCount++;

	if (transform.position.y > 360 || moveCount * moveDistance > 200)
		breakaway = true;
}

void MachineGunShell::Draw(HDC hdc)
{
	DrawEllipse(hdc, transform, color);
}