#include "WaterTurbine.h"

WaterTurbine::WaterTurbine()
{
	name = "WaterTurbine";
	gate = "Output";
}

void WaterTurbine::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 15;
}

void WaterTurbine::Draw(HDC hdc)
{
	Position center;
	center.x = transform.position.x + transform.scale.width / 2;
	center.y = transform.position.y + transform.scale.height / 2;

	int length = transform.scale.width / 2;

	static int angle;
	if (CheckElectric() == false)
		angle = 0;
	else
		angle += 3;

	for (int i = 0; i < 3; i++)
	{
		Position a = AnglePosition(center, length / 2, angle + (60 * i));
		Position b = AnglePosition(center, length / 2, angle + 180 + (60 * i));

		DrawLine(hdc, a, b, 7, RED);
	}

	Transform frame;
	frame.position.x = transform.position.x + transform.scale.width / 4 - 3;
	frame.position.y = transform.position.y + transform.scale.height / 4 - 3;
	frame.scale.width = transform.scale.width / 2 + 7;
	frame.scale.height = transform.scale.height / 2 + 7;

	DrawEllipseEmpty(hdc, frame, 7, RED);
	DrawEllipseEmpty(hdc, frame, 1, BLACK);
}

WaterTurbine::~WaterTurbine()
{

}