#include "Shell.h"

Shell::Shell()
{
	target = NULL;
	breakaway = false;
}

void Shell::SetColor(COLORREF color)
{
	this->color = color;
}

void Shell::SetTarget(Unit* target)
{
	this->target = target;
}

COLORREF Shell::GetColor()
{
	return color;
}

string Shell::GetType()
{
	return type;
}

int Shell::GetDamage()
{
	return damage;
}

Unit* Shell::GetTarget()
{
	return target;
}

void Shell::DeleteTarget()
{
	target = NULL;
}

bool Shell::CheckBreakAway()
{
	int x = transform.position.x;
	int y = transform.position.y;

	if (x < 0 || x > 1280 || y < 0 || y > 540 || breakaway == true)
		return true;
	return false;
}