#include "ResourceGauge.h"

ResourceGauge::ResourceGauge(int resourceMax)
{
	resource = 0;
	this->resourceMax = resourceMax;
}

void ResourceGauge::PurchaseUnit(int unitResource)
{
	resource -= unitResource;
}

void ResourceGauge::EarnResource(int resource)
{
	this->resource += resource;

	if (this->resource > resourceMax)
		this->resource = resourceMax;
}

int ResourceGauge::GetResource()
{
	return resource;
}

void ResourceGauge::Draw(HDC hdc)
{
	DrawRectangle(hdc, transform, WHITE);

	Transform gauge;

	gauge.position.x = transform.position.x + 2;
	gauge.position.y = transform.position.y + 2;

	gauge.scale.width = (float)transform.scale.width / resourceMax * resource - 4;
	if (gauge.scale.width < 0)
		gauge.scale.width = 0;
	gauge.scale.height = transform.scale.height - 4;

	DrawRectangle(hdc, gauge, BLACK);

	TCHAR gaugeNum[512];
	sprintf(gaugeNum, TEXT("%d / %d"), resource, resourceMax);

	Transform gaugeText;
	gaugeText.position = { transform.position.x + transform.scale.width / 4, gauge.position.y };
	gaugeText.scale = { transform.scale.width / 2 - 4, gauge.scale.height };

	DrawTextOut(hdc, gaugeText, gaugeNum, RGB(128, 128, 128));
}