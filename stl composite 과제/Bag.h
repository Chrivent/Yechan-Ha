#pragma once

#include "Inventory.h"
#include "Weapon.h"

class Bag : public Inventory
{
private:
	Weapon* weapon;

public:
	Bag()
	{
		weapon = NULL;
	}

	void AddWeapon(Weapon* weapon)
	{
		if (this->weapon != NULL)
			this->weapon = NULL;

		this->weapon = weapon;
	}

	Weapon* GetWeapon()
	{
		return weapon;
	}
};