#include "ConnectingWire.h"

ConnectingWire::ConnectingWire(int type)
{
	name = "ConnectingWire";

	for (int direction = DIRECTION_U; direction < DIRECTION_COUNT; direction++)
		wire[direction] = false;

	switch (type)
	{
	case 1:
		wire[DIRECTION_U] = true;
		break;

	case 2:
		wire[DIRECTION_R] = true;
		break;

	case 3:
		wire[DIRECTION_D] = true;
		break;

	case 4:
		wire[DIRECTION_L] = true;
		break;

	case 5:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_R] = true;
		break;

	case 6:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_D] = true;
		break;

	case 7:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_L] = true;
		break;

	case 8:
		wire[DIRECTION_R] = true;
		wire[DIRECTION_D] = true;
		break;

	case 9:
		wire[DIRECTION_R] = true;
		wire[DIRECTION_L] = true;
		break;

	case 10:
		wire[DIRECTION_D] = true;
		wire[DIRECTION_L] = true;
		break;

	case 11:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_R] = true;
		wire[DIRECTION_D] = true;
		break;

	case 12:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_R] = true;
		wire[DIRECTION_L] = true;
		break;

	case 13:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_D] = true;
		wire[DIRECTION_L] = true;
		break;

	case 14:
		wire[DIRECTION_R] = true;
		wire[DIRECTION_D] = true;
		wire[DIRECTION_L] = true;
		break;

	case 15:
		wire[DIRECTION_U] = true;
		wire[DIRECTION_R] = true;
		wire[DIRECTION_D] = true;
		wire[DIRECTION_L] = true;
		break;

	default:
		break;
	}
}

bool ConnectingWire::CheckWireExist(int direction)
{
	return wire[direction];
}

void ConnectingWire::IncreaseVoltage()
{
	if (voltage < 255)
		voltage += 15;
}

void ConnectingWire::Draw(HDC hdc)
{
	Transform tmp[DIRECTION_COUNT];

	tmp[DIRECTION_U].position = { transform.position.x + transform.scale.width / 7 * 3, transform.position.y };
	tmp[DIRECTION_U].scale = { transform.scale.width / 7, transform.scale.height / 2 };

	tmp[DIRECTION_R].position = { transform.position.x + transform.scale.width / 2, transform.position.y + transform.scale.height / 7 * 3 };
	tmp[DIRECTION_R].scale = { tmp[DIRECTION_U].scale.height, tmp[DIRECTION_U].scale.width };

	tmp[DIRECTION_D].position = { tmp[DIRECTION_U].position.x, transform.position.y + transform.scale.height / 2 };
	tmp[DIRECTION_D].scale = { tmp[DIRECTION_U].scale.width, tmp[DIRECTION_U].scale.height };

	tmp[DIRECTION_L].position = { transform.position.x, tmp[DIRECTION_R].position.y };
	tmp[DIRECTION_L].scale = { tmp[DIRECTION_U].scale.height, tmp[DIRECTION_U].scale.width };

	Transform center;
	center.position = { transform.position.x + transform.scale.width / 5 * 2, transform.position.y + transform.scale.height / 5 * 2 };
	center.scale = { transform.scale.width / 5, transform.scale.height / 5 };

	COLORREF color;
	color = RGB(255 - voltage, 0 + voltage, 0);

	for (int direction = DIRECTION_U; direction < DIRECTION_COUNT; direction++)
	{
		if (wire[direction] == true)
			DrawRectangle(hdc, tmp[direction], color);
	}

	DrawEllipse(hdc, center, color);
}

ConnectingWire::~ConnectingWire()
{
}