#include "Player.h"

Player::Player()
{
}

void Player::DrawStatus(int x, int y, int color)
{
	m_draw.TextMiddle(x, y, "====== " + m_name + "(" + to_string(m_rank) + "Lv) ======", color);
	m_draw.TextMiddle(x, y + 1, "공격력 = " + to_string(m_damage) + "\t생명력 = " + to_string(m_hp) + "/" + to_string(m_hpMax), color);
	m_draw.TextMiddle(x, y + 2, "경험치 = " + to_string(m_exp) + "/" + to_string(m_expMax) + "\tGetEXP : " + to_string(m_getExp), color);
	m_draw.TextMiddle(x, y + 3, "Gold = " + to_string(m_gold), color);

	if (m_weapon != NULL)
		m_draw.TextMiddle(x, y + 4, "무기 타입 : " + m_weapon->GetType() + " 무기 이름 : " + m_weapon->GetName() + " 공격력 : " + to_string(m_weapon->GetDamage()), color);
}

void Player::SetName(int x, int y)
{
	m_draw.TextMiddle(x, y,"Player 이름 입력 : ", YELLOW);
	m_name = InputStr(YELLOW);
}

void Player::SetWeapon(Weapon* weapon, string type)
{
	if (m_weapon != NULL)
	{
		delete m_weapon;
		m_weapon = NULL;
	}

	if (type == "Dagger")
		m_weapon = new Dagger;
	else if (type == "Gun")
		m_weapon = new Gun;
	else if (type == "Sword")
		m_weapon = new Sword;
	else if (type == "Wand")
		m_weapon = new Wand;
	else if (type == "Bow")
		m_weapon = new Bow;
	else if (type == "Hammer")
		m_weapon = new Hammer;

	m_weapon->SetStatus(type, weapon->GetName(), weapon->GetPrice(), weapon->GetDamage());
}

Weapon* Player::GetWeapon()
{
	return m_weapon;
}

void Player::RankUp()
{
	m_rank++;
	m_damage *= 2;
	m_hpMax *= 2;
	m_expMax *= 2;
	m_getExp *= 2;
}

int Player::GetDamage()
{
	int damage = m_damage;

	if (m_weapon != NULL)
		damage += m_weapon->GetDamage();

	return damage;
}

void Player::Event(int x, int y, Character* enemy, int result)
{
	if (m_weapon != NULL)
		m_weapon->SkillEvent(x, y, this, enemy, result);
	else
	{
		if (result == RESULT_WIN)
		{
			enemy->DecreaseHp(m_damage);
			m_draw.TextMiddle(x, y, "데미지 : " + to_string(m_damage));
		}
		else if (result == RESULT_LOSE)
			m_hp-= enemy->GetDamage();
	}
}

Player::~Player()
{
	if (m_weapon != NULL)
		delete m_weapon;
}
