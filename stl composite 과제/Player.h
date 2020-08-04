#pragma once

#include "Character.h"
#include "Dagger.h"
#include "Gun.h"
#include "Sword.h"
#include "Wand.h"
#include "Bow.h"
#include "Hammer.h"
#include "Bag.h"

class Player : public Character
{
private:
	//Weapon* m_weapon;
	Bag* bag;

public:
	Player();

	void DrawStatus(int x, int y, int color = ORIGINAL);
	void SetName(int x, int y);
	void SetWeapon(Weapon* weapon, string type);
	Weapon* GetWeapon();
	void RankUp();
	int GetDamage();
	void Event(int x, int y, Character* enemy, int result);

	~Player();
};