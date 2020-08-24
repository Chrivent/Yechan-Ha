#pragma once

#include "mecro.h"
#include "Character.h"
#include "Inventory.h"

enum RESULT
{
	RESULT_WIN,
	RESULT_LOSE,
	RESULT_TIE
};

class Weapon : public Inventory
{
protected:
	Draw m_draw;
	int m_price;
	string m_type;
	string m_name;
	int m_damage;

public:
	Weapon();

	void DrawStatus(int x, int y);
	void SetStatus(string type, string name, int price, int damage);
	string GetType();
	string GetName();
	int GetPrice();
	int GetDamage();
	virtual void SkillEvent(int x, int y, Character* player, Character* enemy, int result) = 0;

	virtual ~Weapon();
};