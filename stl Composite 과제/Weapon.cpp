#include "Weapon.h"

Weapon::Weapon()
{
}

void Weapon::DrawStatus(int x, int y)
{
	m_draw.TextMiddle(x, y, "���� : " + to_string(m_price) + " ���� Ÿ�� : " + m_type, YELLOW);
	m_draw.TextMiddle(x, y + 1, "���� �̸� : " + m_name + " ���ݷ� : " + to_string(m_damage), YELLOW);
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