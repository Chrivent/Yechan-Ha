#include "SolarPanel.h"

SolarPanel::SolarPanel()
{
	name = "SolarPanel";
	gate = "Output";
}

void SolarPanel::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 15;
}

void SolarPanel::Draw(HDC hdc)
{
	Transform panel[2][2];

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			panel[y][x].position.x = transform.position.x + (transform.scale.width / 4) * (x + 1);
			panel[y][x].position.y = transform.position.y + (transform.scale.height / 4) * (y + 1);
			panel[y][x].scale.width = transform.scale.width / 4;
			panel[y][x].scale.height = transform.scale.height / 4;

			DrawRectangleCustom(hdc, panel[y][x], 1, (CheckElectric() == false) ? WHITE : YELLOW, RGB(128, 128, 128));
		}
	}
}

SolarPanel::~SolarPanel()
{

}