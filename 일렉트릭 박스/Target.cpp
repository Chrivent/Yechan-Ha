#include "Target.h"

Target::Target()
{
	name = "Target";
	gate = "Input";
}

void Target::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 15;
}

void Target::Draw(HDC hdc)
{
	DrawRectangleCustom(hdc, transform, 5, RGB(128, 128, 128), BLACK);

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

		DrawLine(hdc, a, b, 7, BLACK);
	}
}

Target::~Target()
{

}