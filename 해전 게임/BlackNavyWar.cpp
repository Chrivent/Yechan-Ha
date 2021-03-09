#include "BlackNavyWar.h"

BlackNavyWar::BlackNavyWar()
{
	for (int i = 0; i < UNIT_MAX; i++)
		unit[i] = NULL;

	for (int i = 0; i < SHELL_MAX; i++)
		shell[i] = NULL;

	unit[0] = new Base;
	unit[1] = new Base;

	UnitInit(unit[0], BLACK);
	UnitInit(unit[1], RED);

	resourceGauge = new ResourceGauge(1000);
	resourceGauge->transform.position = { 640, 622 };
	resourceGauge->transform.scale = { 320, 16 };

	for (int i = 0; i < UNIT_COUNT; i++)
	{
		button[i] = new Button('1' + i);

		button[i]->transform.position = { 50 * i + 10, 622};
		button[i]->transform.scale = { 40, 40 };
	}
}

void BlackNavyWar::UnitInit(Unit* thisUnit, COLORREF color)
{
	thisUnit->SetColor(color);
	thisUnit->SetPositionOrigin();
	thisUnit->CreateLifeGauge();
}

void BlackNavyWar::CreateUnit(char unitID)
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] == NULL)
		{
			switch (unitID)
			{
			case '1':
				unit[i] = new Corvette;
				break;

			case '2':
				unit[i] = new Frigate;
				break;

			case '3':
				unit[i] = new Submarine;
				break;

			case '4':
				unit[i] = new TorpedoBomber;
				break;

			case '5':
				unit[i] = new Helicopter;
				break;

			case '6':
				unit[i] = new Destroyer;
				break;

			case '7':
				unit[i] = new Cruiser;
				break;
			}

			if (resourceGauge->GetResource() >= unit[i]->GetResource())
			{
				resourceGauge->PurchaseUnit(unit[i]->GetResource());
				UnitInit(unit[i], BLACK);
			}
			else
			{
				delete unit[i];
				unit[i] = NULL;
			}

			break;
		}
	}
}

void BlackNavyWar::CreateEnemyUnit()
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] == NULL)
		{
			char unitID = RandNum('1', '7');

			switch (unitID)
			{
			case '1':
				unit[i] = new Corvette;
				break;

			case '2':
				unit[i] = new Frigate;
				break;

			case '3':
				unit[i] = new Submarine;
				break;

			case '4':
				unit[i] = new TorpedoBomber;
				break;

			case '5':
				unit[i] = new Helicopter;
				break;

			case '6':
				unit[i] = new Destroyer;
				break;

			case '7':
				unit[i] = new Cruiser;
				break;
			}

			UnitInit(unit[i], RED);

			break;
		}
	}
}

void BlackNavyWar::MoveUnit(char unitID)
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL && unit[i]->GetUnitID() == unitID)
			unit[i]->Move();
	}
}

Unit* BlackNavyWar::GetDetectUnit(Unit* thisUnit)
{
	bool detectShip = thisUnit->GetDetectType(TYPE_SHIP);
	bool detectSubmersible = thisUnit->GetDetectType(TYPE_SUBMERSIBLE);
	bool detectAircraft = thisUnit->GetDetectType(TYPE_AIRCRAFT);

	int thisX = thisUnit->transform.position.x;

	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL && unit[i]->GetColor() != thisUnit->GetColor())
		{
			bool detectUnit = false;

			string type = unit[i]->GetType();

			int unitX = unit[i]->transform.position.x;
			int distance = (unitX >= thisX) ? unitX - thisX : thisX - unitX;

			int detectDistance;
			if (detectShip && type == "Ship")
			{
				detectDistance = thisUnit->GetDetectShipDistance();
				detectUnit = true;
			}
			if (detectSubmersible && type == "Submersible")
			{
				detectDistance = thisUnit->GetDetectSubmersibleDistance();
				detectUnit = true;
			}
			if (detectAircraft && type == "Aircraft")
			{
				detectDistance = thisUnit->GetDetectAircraftDistance();
				detectUnit = true;
			}
			if (type == "Base")
			{
				detectDistance = 40;
				detectUnit = true;
			}

			if (detectUnit == true && distance <= detectDistance + thisUnit->transform.scale.width)
				return unit[i];
		}
	}
	return NULL;
}

void BlackNavyWar::DetectUnitEvent()
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL && unit[i]->GetTarget() == NULL)
		{
			Unit* target = GetDetectUnit(unit[i]);

			if (target != NULL)
				unit[i]->SetTarget(target);
		}
	}
}

void BlackNavyWar::CreateShell(Unit* thisUnit, Unit* target, string type)
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] == NULL)
		{
			COLORREF unitColor = thisUnit->GetColor();

			Position unitPosition = thisUnit->transform.position;
			Scale unitScale = thisUnit->transform.scale;

			Scale targetScale = target->transform.scale;

			Position targetPosition;
			if (target->GetType() != "Base")
			{
				targetPosition.x = target->transform.position.x + targetScale.width / 2;
				targetPosition.y = target->transform.position.y + targetScale.height / 2;
			}
			else
			{
				targetPosition.x = (target->GetColor() == RED) ? target->transform.position.x : (target->transform.position.x + targetScale.width);
				targetPosition.y = target->transform.position.y + targetScale.height / 2;
			}

			if (type == "MachineGun_a" || type == "MachineGun_s")
			{
				Position blackPosition = { unitPosition.x + unitScale.width, unitPosition.y + unitScale.height / 2 };
				Position redPosition = { unitPosition.x, unitPosition.y + unitScale.height / 2 };

				Position shellPosition = (unitColor == BLACK) ? blackPosition : redPosition;

				float angle = PositionAngle(shellPosition, targetPosition);
				shell[i] = new MachineGunShell(angle, type);

				shell[i]->transform.position = shellPosition;
				shell[i]->SetColor(unitColor);

				break;
			}
			else if (type == "Torpedo")
			{
				Position blackPosition = { unitPosition.x + unitScale.width, unitPosition.y + unitScale.height / 2 };
				Position redPosition = { unitPosition.x, unitPosition.y + unitScale.height / 2 };

				Position shellPosition = (unitColor == BLACK) ? blackPosition : redPosition;

				shell[i] = new TorpedoShell(target);

				shell[i]->transform.position = shellPosition;
				shell[i]->SetColor(unitColor);

				break;
			}
			else if (type == "DepthCharge" && target->GetType() != "Base")
			{
				int count = 0;
				int offset = 0;
				int distance = unitScale.width + thisUnit->GetDetectSubmersibleDistance();

				for (int j = 0; j < SHELL_MAX; j++)
				{
					if (shell[j] == NULL)
					{
						shell[j] = new DepthChargeShell;
						shell[j]->SetColor(unitColor);
						shell[j]->transform.position = { unitPosition.x + ((unitColor == BLACK) ? distance : -distance) + offset, 360 };

						Submarine tmpSubmarine;
						offset += tmpSubmarine.transform.scale.width / 5;
						count++;
					}
					
					if (count == 5)
						break;
				}

				break;
			}
			else if (type == "Shrapnel" && target->GetType() != "Base")
			{
				Position shellPosition = { unitPosition.x + unitScale.width / 2, unitPosition.y };
				float angle = PositionAngle(shellPosition, targetPosition);
				float angle2 = 0;
				int count = 0;

				for (int j = 0; j < SHELL_MAX; j++)
				{
					if (shell[j] == NULL)
					{
						shell[j] = new ShrapnelShell(targetPosition, angle, angle2);
						shell[j]->SetColor(unitColor);
						shell[j]->transform.position = shellPosition;

						angle2 += 30;
						count++;
					}

					if (count == 12)
						break;
				}

				break;
			}
			else if (type == "Missile")
			{
				Position shellPosition = { unitPosition.x + unitScale.width / 2, unitPosition.y };

				shell[i] = new MissileShell(target);

				shell[i]->transform.position = shellPosition;
				shell[i]->SetColor(unitColor);

				break;
			}
		}
	}
}

void BlackNavyWar::Fire(string type)
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL && unit[i]->CheckWeapon(type))
		{
			Unit* target = unit[i]->GetTarget();

			if (target != NULL && target->CheckAntiWeapon(type))
				CreateShell(unit[i], target, type);
		}
	}
}

void BlackNavyWar::MoveShell(string type)
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] != NULL && shell[i]->GetType() == type)
			shell[i]->Move();
	}
}

void BlackNavyWar::HitUnitEvent()
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] != NULL)
		{
			Unit* target = GetHitUnit(shell[i]);

			if (target != NULL)
			{
				target->DecreaseLife(shell[i]->GetDamage());
				delete shell[i];
				shell[i] = NULL;
			}
		}
	}
}

Unit* BlackNavyWar::GetHitUnit(Shell* thisShell)
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL && CheckTransformIsIntersect(unit[i]->transform, thisShell->transform))
		{
			if (unit[i]->CheckAntiWeapon(thisShell->GetType()) && unit[i]->GetColor() != thisShell->GetColor())
				return unit[i];
		}
	}
	return NULL;
}

void BlackNavyWar::IncreaseResource()
{
	resourceGauge->EarnResource(1);
}

void BlackNavyWar::ExhaustLifeEvent()
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL && unit[i]->CheckLifeIsExhausted())
		{
			for (int j = 0; j < UNIT_MAX; j++)
			{
				if (unit[j] != NULL && unit[j]->GetTarget() == unit[i])
					unit[j]->DeleteTarget();
			}

			for (int j = 0; j < SHELL_MAX; j++)
			{
				if (shell[j] != NULL && shell[j]->GetTarget() == unit[i])
					shell[j]->DeleteTarget();
			}

			if (unit[i]->GetColor() == RED)
				resourceGauge->EarnResource(unit[i]->GetResource());

			delete unit[i];
			unit[i] = NULL;
		}
	}
}

void BlackNavyWar::DestroyShellTargetEvent()
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] != NULL && shell[i]->GetTarget() == NULL)
		{
			Unit* tmp = NULL;
			for (int j = 0; j < UNIT_MAX; j++)
			{
				if (unit[j] != NULL && unit[j]->CheckAntiWeapon(shell[i]->GetType()) && unit[j]->GetColor() != shell[i]->GetColor())
				{
					if (tmp == NULL)
						tmp = unit[j];
					else
					{
						int distance = unit[j]->transform.position.x - shell[i]->transform.position.x;
						if (distance < 0)
							distance *= -1;

						int distance2 = tmp->transform.position.x - shell[i]->transform.position.x;
						if (distance2 < 0)
							distance2 *= -1;

						if (distance < distance2)
							tmp = unit[j];
					}
				}
			}

			shell[i]->SetTarget(tmp);
		}
	}
}

void BlackNavyWar::BreakawayShellEvent()
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] != NULL && shell[i]->CheckBreakAway())
		{
			delete shell[i];
			shell[i] = NULL;
		}
	}
}

void BlackNavyWar::EnoughResourceEvent()
{
	for (int i = 0; i < UNIT_COUNT; i++)
	{
		if (button[i]->GetResource() <= resourceGauge->GetResource())
			button[i]->On();
		else
			button[i]->Off();
	}
}

void BlackNavyWar::MouseClickEvent(LPARAM lParam)
{
	for (int i = 0; i < UNIT_COUNT; i++)
	{
		if (CheckPositionIsInTransform(button[i]->transform, MousePosition(lParam)))
		{
			CreateUnit(button[i]->GetUnitID());
			break;
		}
	}
}

void BlackNavyWar::Draw(HDC hdc)
{
	DrawRectangle(hdc, { { 0, 0 }, { 1280, 540 } }, RGB(128, 128, 128));
	DrawLine(hdc, { 0, OCEAN_HEIGHT }, { 1280, OCEAN_HEIGHT }, 2, BLACK);

	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL)
			unit[i]->Draw(hdc);
	}

	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] != NULL)
			shell[i]->Draw(hdc);
	}

	resourceGauge->Draw(hdc);

	for (int i = 0; i < UNIT_COUNT; i++)
		button[i]->Draw(hdc);
}

BlackNavyWar::~BlackNavyWar()
{
	for (int i = 0; i < UNIT_MAX; i++)
	{
		if (unit[i] != NULL)
		{
			delete unit[i];
			unit[i] = NULL;
		}
	}

	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shell[i] != NULL)
		{
			delete shell[i];
			shell[i] = NULL;
		}
	}

	if (resourceGauge != NULL)
	{
		delete resourceGauge;
		resourceGauge = NULL;
	}

	for (int i = 0; i < UNIT_COUNT; i++)
	{
		if (button[i] != NULL)
		{
			delete button[i];
			button[i] = NULL;
		}
	}
}