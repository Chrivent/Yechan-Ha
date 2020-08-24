#include "Map.h"

Map::Map()
{
	m_scale = { 1, 1 };
}

void Map::DrawBox()
{
	m_draw.Box(0, 0, m_scale.width * 32, m_scale.height * 32, BLUE);
}

void Map::EraseBoxInner()
{
	m_draw.Rectangle(1, 1, m_scale.width * 30, m_scale.height * 30, "  ");
}

void Map::DrawMain()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 12, "☆★ DonGeonRPG ★☆");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 15, "New Game");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 18, "Load Game");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 21, "Game Exit");
}

void Map::DrawPlay()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 9, "☆★ Menu ★☆");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 11, "Dongeon");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 13, "Player Info");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 15, "Monster Info");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 17, "Weapon Shop");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 19, "Save");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 21, "Exit");
}

void Map::DrawDongeon()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 6, "===== 던전 입구 =====");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 11, "1층 던전 : [고블린]");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 13, "2층 던전 : [오크]");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 15, "3층 던전 : [늑대인간]");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 17, "4층 던전 : [오우거]");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 19, "5층 던전 : [스켈레톤아처]");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 21, "6층 던전 : [리치]");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 23, "돌아가기");
}

void Map::DrawShop()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 9, "♧ ♣ S H O P ♣ ♧");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 11, "Dagger");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 13, "Gun");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 15, "Sword");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 17, "Wand");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 19, "Bow");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 21, "Hammer");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 23, "돌아가기");
}

void Map::DrawSlot(int num, bool saved, int slotCount)
{
	int height = m_scale.height * (3 + m_scale.height * num * 2);
	m_draw.TextMiddle(m_scale.width * 16, height, to_string(num) + "번 슬롯 : (파일 여부 : " + (saved ? "O" : "X") + ")", GREEN);

	if (num == slotCount)
		m_draw.TextMiddle(m_scale.width * 16, height + m_scale.height * 2, to_string(num + 1) + ". 돌아가기", GREEN);
}

void Map::DrawSaved()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 16, "Save 완료");
}

void Map::DrawNoData()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 16, "해당 파일이 없습니다.");
}

void Map::DrawLoaded()
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 16, "Load 완료");
}

void Map::DrawStage()
{
	m_draw.TextMiddle(m_scale.width * 8, m_scale.height * 9, "가위 : 1", YELLOW);
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 9, "바위 : 2", YELLOW);
	m_draw.TextMiddle(m_scale.width * 24, m_scale.height * 9, "보 : 3", YELLOW);
	m_draw.WidthLine(m_scale.width * 1, m_scale.height * 16, (m_scale.width * 15) - 1, "--", RED);
	m_draw.Text(m_scale.width * 16, m_scale.height * 16, "vs", RED);
	m_draw.WidthLine((m_scale.width * 16) + 2, m_scale.height * 16, (m_scale.width * 14) - 1, "--", RED);
}

void Map::DrawSelectWeapon(int gold, string type)
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 3, "보유 Gold : " + to_string(gold));
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 5, type + " Shop");
}

void Map::DrawSelectPage(int y)
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * y, "이전 페이지");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * (y + 3), "다음 페이지");
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * (y + 6), "나가기");
}

void Map::DrawHand(int playerHand, int enemyHand, string pl_result, string en_result)
{
	string pl_hand;
	string en_hand;

	switch (playerHand)
	{
	case 1:
		pl_hand = "가위";
		break;
	case 2:
		pl_hand = "바위";
		break;
	case 3:
		pl_hand = "보";
		break;
	default:
		break;
	}

	switch (enemyHand)
	{
	case 1:
		en_hand = "가위";
		break;
	case 2:
		en_hand = "바위";
		break;
	case 3:
		en_hand = "보";
		break;
	default:
		break;
	}

	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 12, pl_hand, YELLOW);
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 13, pl_result, RED);
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 18, en_result, RED);
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 19, en_hand);
}

void Map::DrawMatchResult(string name, int getExp)
{
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 9, name + " 승리!!", RED);
	m_draw.TextMiddle(m_scale.width * 16, m_scale.height * 12, name + "가 경험치 " + to_string(getExp) + "를 얻었습니다.", RED);
}

int Map::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	m_draw.Point(x, y, "▷", RED);
	int Select = 1;
	while (true)
	{
		switch (getch())
		{
		case 'w':
			if (Select - 1 >= 1)
			{
				m_draw.Point(x, y, "  ");
				y -= AddCol;
				Select--;
			}
			break;
		case 's':
			if (Select + 1 <= MenuLen)
			{
				m_draw.Point(x, y, "  ");
				y += AddCol;
				Select++;
			}
			break;
		case ENTER:
			return Select;
		}
		m_draw.Point(x, y, "▷", RED);
	}
}

Scale Map::GetScale()
{
	return m_scale;
}

Map::~Map()
{

}