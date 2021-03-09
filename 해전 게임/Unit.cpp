#include "Unit.h"

Unit::Unit()
{
	target = NULL;
	lifeGauge = NULL;
}

void Unit::SetColor(COLORREF color)
{
	this->color = color;
}

void Unit::SetTarget(Unit* target)
{
	this->target = target;
}

COLORREF Unit::GetColor()
{
	return color;
}

char Unit::GetUnitID()
{
	return unitID;
}

string Unit::GetType()
{
	return type;
}

int Unit::GetDetectShipDistance()
{
	return detectShipDistance;
}

int Unit::GetDetectSubmersibleDistance()
{
	return detectSubmersibleDistance;
}

int Unit::GetDetectAircraftDistance()
{
	return detectAircraftDistance;
}

bool Unit::GetDetectType(TYPE type)
{
	return detectType[type];
}

Unit* Unit::GetTarget()
{
	return target;
}

int Unit::GetResource()
{
	return resource;
}

void Unit::CreateLifeGauge()
{
	lifeGauge = new LifeGauge(life);
	lifeGauge->transform = transform;
}

void Unit::Move()
{
	lifeGauge->transform = transform;
	MoveUnit();
}

void Unit::DecreaseLife(int damage)
{
	lifeGauge->DecreaseLife(damage);
}

bool Unit::CheckLifeIsExhausted()
{
	return lifeGauge->CheckLifeIsExhausted();
}

void Unit::DeleteTarget()
{
	target = NULL;
}

void Unit::Draw(HDC hdc)
{
	if (lifeGauge != NULL)
		lifeGauge->Draw(hdc);

	DrawUnit(hdc);
}

Unit::~Unit()
{
	if (lifeGauge != NULL)
	{
		delete lifeGauge;
		lifeGauge = NULL;
	}
}