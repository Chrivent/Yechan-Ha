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

	void SetStatus(string name, int rank, int damage, int hp, int hpMax, int exp, int expMax, int getExp, int gold);
	void DrawStatus(int x, int y, int color = ORIGINAL);

	string GetName();
	int GetRank();
	int GetDamage();
	int GetHp();
	int GetHpMax();
	int GetExp();
	int GetExpMax();
	int Get_getExp();
	int GetGold();

	void IncreaseExp(int exp);
	void IncreaseGold(int gold);
	void DecreaseGold(int gold);
	void DecreaseHp(int hp);

	void ResetHp();
	void RankUp();

	~Character();
};

