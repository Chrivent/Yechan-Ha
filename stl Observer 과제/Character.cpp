#include "Character.h"

Character::Character()
{
}

void Character::SetStatus(string name, int rank, int damage, int hp, int hpMax, int exp, int expMax, int getExp, int gold)
{
	m_name = name;
	m_rank = rank;
	m_damage = damage;
	m_hp = hp;
	m_hpMax = hpMax;
	m_exp = exp;
	m_expMax = expMax;
	m_getExp = getExp;
	m_gold = gold;
}

void Character::DrawStatus(int x, int y, int color)
{
	m_draw.TextMiddle(x, y, "====== " + m_name + "(" + to_string(m_rank) + "Lv) ======", color);
	m_draw.TextMiddle(x, y + 1, "공격력 = " + to_string(m_damage) + "\t생명력 = " + to_string(m_hp) + "/" + to_string(m_hpMax), color);
	m_draw.TextMiddle(x, y + 2, "경험치 = " + to_string(m_exp) + "/" + to_string(m_expMax) + "\tGetEXP : " + to_string(m_getExp), color);
	m_draw.TextMiddle(x, y + 3, "Gold = " + to_string(m_gold), color);
}

string Character::GetName()
{
	return m_name;
}

int Character::GetRank()
{
	return m_rank;
}

int Character::GetDamage()
{
	return m_damage;
}

int Character::GetHp()
{
	return m_hp;
}

int Character::GetHpMax()
{
	return m_hpMax;
}

int Character::GetExp()
{
	return m_exp;
}

int Character::GetExpMax()
{
	return m_expMax;
}

int Character::Get_getExp()
{
	return m_getExp;
}

int Character::GetGold()
{
	return m_gold;
}

void Character::IncreaseExp(int exp)
{
	m_exp += exp;

	while (m_exp >= m_expMax)
	{
		m_exp -= m_expMax;
		RankUp();
	}
}

void Character::IncreaseGold(int gold)
{
	m_gold += gold;
}

void Character::DecreaseGold(int gold)
{
	m_gold -= gold;
}

void Character::DecreaseHp(int hp)
{
	m_hp -= hp;
}

void Character::ResetHp()
{
	m_hp = m_hpMax;
}

void Character::RankUp()
{
	m_rank++;
	m_damage *= 2;
	m_hpMax *= 2;
	m_expMax *= 2;
	m_getExp *= 2;
	m_gold *= 2;
}

Character::~Character()
{
}