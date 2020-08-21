#pragma once

#include "Character.h"
#include "Observer.h"

class Enemy : public Character, public Observer
{
private:
	bool m_live;

public:
	Enemy();

	void Update();
	void SetLive(bool live);
	bool CheckLive();

	~Enemy();
};