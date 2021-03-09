#include "Button.h"

Button::Button(char unitID)
{
	on = false;

	switch (unitID)
	{
	case '1':
		unit = new Corvette;
		break;

	case '2':
		unit = new Frigate;
		break;

	case '3':
		unit = new Submarine;
		break;

	case '4':
		unit = new TorpedoBomber;
		break;

	case '5':
		unit = new Helicopter;
		break;

	case '6':
		unit = new Destroyer;
		break;

	case '7':
		unit = new Cruiser;
		break;
	}
	unit->SetColor(BLACK);
}

int Button::GetResource()
{
	return unit->GetResource();
}

void Button::On()
{
	on = true;
}

void Button::Off()
{
	on = false;
}

char Button::GetUnitID()
{
	return unit->GetUnitID();
}

void Button::Draw(HDC hdc)
{
	DrawRectangle(hdc, transform, (on == true) ? WHITE : RGB(128, 128, 128));

	Transform tmp;
	tmp.scale = { transform.scale.width / 2, unit->transform.scale.height / (unit->transform.scale.width / (transform.scale.width / 2)) };
	tmp.position = { transform.position.x + (transform.scale.width - tmp.scale.width) / 2, transform.position.y + (transform.scale.height - tmp.scale.height) / 2 };

	unit->transform = tmp;

	unit->Draw(hdc);

	TCHAR resourceNum[512];
	sprintf(resourceNum, TEXT("%d"), unit->GetResource());

	Transform resourceText;
	resourceText.position = { transform.position.x + transform.scale.width / 3, transform.position.y + transform.scale.height };
	resourceText.scale = { transform.scale.width / 3, transform.scale.height / 3 };

	DrawTextOut(hdc, resourceText, resourceNum, WHITE);
}

Button::~Button()
{
	if (unit != NULL)
	{
		delete unit;
		unit = NULL;
	}
}