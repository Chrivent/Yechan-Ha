#include "Hammer.h"

Hammer::Hammer()
{
}

void Hammer::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();
		m_draw.TextMiddle(x, y, "������ : " + to_string(damage));

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
		player->DecreaseHp(enemy->GetDamage());
	else if (result == RESULT_TIE)
	{
		int damage = player->GetDamage();
		if (RandBool(3, 1))
			m_draw.TextMiddle(x, y, "�ı� �ߵ�! (���º��϶��� ������ ��ȿ) ������ : " + to_string(damage));

		enemy->DecreaseHp(damage);
	}
}

Hammer::~Hammer()
{
}
