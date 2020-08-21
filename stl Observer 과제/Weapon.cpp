#include "Weapon.h"

Weapon::Weapon()
{
}

void Weapon::DrawStatus(int x, int y)
{
	m_draw.TextMiddle(x, y, "가격 : " + to_string(m_price) + " 무기 타입 : " + m_type, YELLOW);
	m_draw.TextMiddle(x, y + 1, "무기 이름 : " + m_name + " 공격력 : " + to_string(m_damage), YELLOW);
}

void Weapon::SetStatus(string type, string name, int price, int damage)
{
	m_type = type;
	m_name = name;
	m_price = price;
	m_damage = damage;
}

string Weapon::GetType()
{
	return m_type;
}

string Weapon::GetName()
{
	return m_name;
}

int Weapon::GetPrice()
{
	return m_price;
}

int Weapon::GetDamage()
{
	return m_damage;
}

Weapon::~Weapon()
{

}