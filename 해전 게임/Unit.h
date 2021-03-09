#pragma once

#include "LifeGauge.h"

#define SHELL_MAX 10000

enum TYPE
{
	TYPE_SHIP,
	TYPE_SUBMERSIBLE,
	TYPE_AIRCRAFT,
	TYPE_COUNT
};

class Unit : public Object
{
protected:
	COLORREF color;
	char unitID;
	string type;
	bool detectType[TYPE_COUNT];
	int detectShipDistance;
	int detectSubmersibleDistance;
	int detectAircraftDistance;
	int life;
	Unit* target;
	LifeGauge* lifeGauge;
	int resource;

public:
	Unit();

	void SetColor(COLORREF color);
	COLORREF GetColor();
	void SetTarget(Unit* target);
	char GetUnitID();
	string GetType();
	int GetDetectShipDistance();
	int GetDetectSubmersibleDistance();
	int GetDetectAircraftDistance();
	bool GetDetectType(TYPE type);
	Unit* GetTarget();
	int GetResource();
	void CreateLifeGauge();
	void Move();
	void DecreaseLife(int damage);
	bool CheckLifeIsExhausted();
	void DeleteTarget();
	void Draw(HDC hdc);

	virtual void SetPositionOrigin() = 0;
	virtual bool CheckWeapon(string type) = 0;
	virtual bool CheckAntiWeapon(string type) = 0;
	virtual void MoveUnit() = 0;
	virtual void DrawUnit(HDC hdc) = 0;

	~Unit();
};