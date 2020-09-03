#include "Mine.h"

void Mine::DrawMine()
{
	Draw draw;
	draw.Point(position.x, position.y, "£À", YELLOW);
}