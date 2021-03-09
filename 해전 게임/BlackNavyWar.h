#pragma once

#include "Corvette.h"
#include "Frigate.h"
#include "Submarine.h"
#include "TorpedoBomber.h"
#include "Helicopter.h"
#include "Destroyer.h"
#include "Cruiser.h"

#include "MachineGunShell.h"
#include "TorpedoShell.h"
#include "DepthChargeShell.h"
#include "ShrapnelShell.h"
#include "MissileShell.h"

#include "ResourceGauge.h"
#include "Button.h"
#include "Base.h"

#define UNIT_MAX 400
#define OCEAN_HEIGHT 360

#define SHELL_MAX 700

#define UNIT_COUNT 7

class BlackNavyWar
{
private:
	Unit* unit[UNIT_MAX];
	Shell* shell[SHELL_MAX];
	ResourceGauge* resourceGauge;
	Button* button[UNIT_COUNT];

public:
	BlackNavyWar();

	void UnitInit(Unit* thisUnit, COLORREF color);
	void CreateUnit(char unitID);
	void CreateEnemyUnit();
	void MoveUnit(char unitID);
	Unit* GetDetectUnit(Unit* thisUnit);
	void DetectUnitEvent();
	void CreateShell(Unit* thisUnit, Unit* target, string type);
	void Fire(string type);
	void MoveShell(string type);
	void HitUnitEvent();
	Unit* GetHitUnit(Shell* thisShell);
	void IncreaseResource();
	void ExhaustLifeEvent();
	void DestroyShellTargetEvent();
	void BreakawayShellEvent();
	void EnoughResourceEvent();
	void MouseClickEvent(LPARAM lParam);

	void Draw(HDC hdc);

	~BlackNavyWar();
};