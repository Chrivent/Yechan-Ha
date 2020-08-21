#include "Bow.h"

Bow::Bow()
{
}

void Bow::SkillEvent(int x, int y, Character* player, Character* enemy, int result)
{
	static int win;
	if (win != 0 && win != 1 && win != 2)
		win = 0;

	if (result == RESULT_WIN)
	{
		int damage = player->GetDamage();

		if (win == 0)
		{
			m_draw.TextMiddle(x, y, "������ : " + to_string(damage));
			win++;
		}
		else if (win == 1)
		{
			damage *= 3;
			m_draw.TextMiddle(x, y, "���� 1�ܰ� �ߵ�! (2�޺��� �������� ũ�� ����) ������ : " + to_string(damage));
			win++;
		}
		else if (win == 2)
		{
			damage *= 9;
			m_draw.TextMiddle(x, y, "���� 2�ܰ� �ߵ�! (3�޺��� �������� �������� ����) ������ : " + to_string(damage));
			win = 0;
		}

		enemy->DecreaseHp(damage);
	}
	else if (result == RESULT_LOSE)
	{
		player->DecreaseHp(enemy->GetDamage());
		win = 0;
	}
	else if (result == RESULT_TIE)
		win = 0;
}

Bow::~Bow()
{
}
