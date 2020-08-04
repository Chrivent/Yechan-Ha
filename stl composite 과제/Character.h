#pragma once

#include "mecro.h"

class Character
{
protected:
	Draw m_draw;
	string m_name;
	int m_rank;
	int m_damage;
	int m_hp;
	int m_hpMax;
	int m_exp;
	int m_expMax;
	int m_getExp;
	int m_gold;

public:
	Character();

	virtual void SetStatus(string name, int rank, int damage, int hp, int hpMax, int exp, int expMax, int getExp, int gold);
	virtual void DrawStatus(int x, int y, int color = ORIGINAL);

	virtual string GetName();
	virtual int GetRank();
	virtual int GetDamage();
	virtual int GetHp();
	virtual int GetHpMax();
	virtual int GetExp();
	virtual int GetExpMax();
	virtual int Get_getExp();
	virtual int GetGold();

	virtual void IncreaseExp(int exp);
	virtual void IncreaseGold(int gold);
	virtual void DecreaseGold(int gold);
	virtual void DecreaseHp(int hp);

	virtual void ResetHp();
	virtual void RankUp();

	virtual ~Character();
};

