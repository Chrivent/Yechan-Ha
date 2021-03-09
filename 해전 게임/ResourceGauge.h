#pragma once

#include "mecro.h"

class ResourceGauge : public Object
{
private:
	int resourceMax;
	int resource;

public:
	ResourceGauge(int resourceMax);

	void PurchaseUnit(int unitResource);
	void EarnResource(int resource);
	int GetResource();
	void Draw(HDC hdc);
};