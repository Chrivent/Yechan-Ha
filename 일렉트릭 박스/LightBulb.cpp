#include "LightBulb.h"

LightBulb::LightBulb()
{
	name = "LightBulb";
	gate = "Input";
}

void LightBulb::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 15;
}

void LightBulb::Draw(HDC hdc)
{
	Transform bulb;
	bulb.position.x = transform.position.x + transform.scale.width / 4;
	bulb.position.y = transform.position.y + transform.scale.height / 6;
	bulb.scale.width = transform.scale.width / 2;
	bulb.scale.height = transform.scale.height / 2;

	DrawEllipseCustom(hdc, bulb, 1, (CheckElectric() == false) ? RGB(128, 128, 0) : RGB(255, 255, 128), BLACK);

	Transform socket;
	socket.position.x = transform.position.x + transform.scale.width / 3;
	socket.position.y = transform.position.y + transform.scale.height / 5 * 3;
	socket.scale.width = transform.scale.width / 3;
	socket.scale.height = transform.scale.height / 4;

	DrawRectangleCustom(hdc, socket, 1, RGB(128, 128, 128), BLACK);
}

LightBulb::~LightBulb()
{

}