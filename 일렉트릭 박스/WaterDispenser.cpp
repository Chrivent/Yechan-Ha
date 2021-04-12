#include "WaterDispenser.h"

WaterDispenser::WaterDispenser()
{
	name = "WaterDispenser";
	gate = "Input";
}

void WaterDispenser::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 15;
}

void WaterDispenser::Draw(HDC hdc)
{
	Transform bucket;
	bucket.position.x = transform.position.x + transform.scale.width / 4;
	bucket.position.y = transform.position.y + transform.scale.height / 4;
	bucket.scale.width = transform.scale.width / 2;
	bucket.scale.height = transform.scale.height / 2;

	DrawRectangleCustom(hdc, bucket, 1, SKYBLUE, RGB(128, 128, 128));

	Transform blank;
	blank.position.x = transform.position.x + transform.scale.width / 4 + 1;
	blank.position.y = transform.position.y + transform.scale.height / 4;
	blank.scale.width = transform.scale.width / 2 - 2;

	static int waterLevel;
	if (CheckElectric() == false)
		waterLevel = 0;
	else
		waterLevel = (waterLevel == 0) ? 2 : 0;
	blank.scale.height = transform.scale.height / 10 + waterLevel;

	DrawRectangle(hdc, blank, WHITE);
	DrawLine(hdc, bucket.position, { bucket.position.x + bucket.scale.width, bucket.position.y }, 4, RGB(128, 128, 128));
}

WaterDispenser::~WaterDispenser()
{

}