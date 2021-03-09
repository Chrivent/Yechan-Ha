#include "DepthChargeShell.h"

DepthChargeShell::DepthChargeShell()
{
	transform.scale = { 8, 6 };
	type = "DepthCharge";
	damage = 4;
}

void DepthChargeShell::Move()
{
	transform.MoveDown();
}

void DepthChargeShell::Draw(HDC hdc)
{
	DrawEllipse(hdc, transform, color);
}