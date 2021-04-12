#include "MainPowerSupply.h"

MainPowerSupply::MainPowerSupply()
{
	name = "MainPowerSupply";
	gate = "Output";
}

void MainPowerSupply::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 255;
}

void MainPowerSupply::Draw(HDC hdc)
{
	DrawRectangleCustom(hdc, transform, 5, RGB(128, 128, 128), BLACK);

	Transform tmp;
	tmp.position.x = transform.position.x + transform.scale.width / 3;
	tmp.position.y = transform.position.y + transform.scale.height / 3;
	tmp.scale.width = transform.scale.width / 3;
	tmp.scale.height = transform.scale.height / 3;

	DrawRectangle(hdc, tmp, (CheckElectric() == false) ? RED : GREEN);
}

MainPowerSupply::~MainPowerSupply()
{

}