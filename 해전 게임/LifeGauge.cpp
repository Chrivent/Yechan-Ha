#include "LifeGauge.h"

LifeGauge::LifeGauge(int life)
{
	this->lifeMax = life;
	this->life = life;
}

void LifeGauge::DecreaseLife(int damage)
{
	life -= damage;
}

bool LifeGauge::CheckLifeIsExhausted()
{
	if (life <= 0)
		return true;
	return false;
}

void LifeGauge::Draw(HDC hdc)
{
	Transform tmp;

	tmp.position.x = transform.position.x;
	tmp.position.y = transform.position.y - 4;

	tmp.scale.width = (float)transform.scale.width / lifeMax * life;
	tmp.scale.height = 2;

	DrawRectangle(hdc, tmp, RED);
}