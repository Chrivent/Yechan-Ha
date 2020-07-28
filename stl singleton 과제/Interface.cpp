#include "Interface.h"

Interface::Interface()
{
	m_sca = { 65, 40 };
}

void Interface::ChangeScreenSize()
{
	SetScreenSize(m_sca.width, m_sca.height);
}

void Interface::DrawMainMenu()
{
	ClearBox();
	m_draw.TextMiddle(m_sca.width / 2, 7, "☆ ★ 베 네 치 아 ★ ☆", BLUE);
	m_draw.TextMiddle(m_sca.width / 2, 14, "1.Game Start", BLUE);
	m_draw.TextMiddle(m_sca.width / 2, 17, "2.Rank", BLUE);
	m_draw.TextMiddle(m_sca.width / 2, 20, "3.Exit", BLUE);
}

void Interface::DrawBox()
{
	m_draw.Box(0, 0, 65, 36, BLUE);
}

void Interface::ClearBox()
{
	m_draw.Rectangle(1, 1, 63, 34, "  ");
}

void Interface::ClearStatus()
{
	m_draw.Rectangle(1, 36, 63, 3, "  ");
}

void Interface::DrawStatus(int life, int score, string name)
{
	ClearStatus();
	m_draw.Text(4, 37, "Life", RED);
	m_draw.WidthLine(4, 38, life, "♥", RED);
	m_draw.TextMiddle(m_sca.width / 2, 37, "Score");
	m_draw.TextMiddle(m_sca.width / 2, 38, to_string(score));
	m_draw.Text((m_sca.width / 8) * 7, 37, "Name");
	m_draw.Text((m_sca.width / 8) * 7, 38, name);
}

void Interface::ShowStory()
{
	ClearBox();
	DrawTextBox();
	m_draw.TextMiddle(m_sca.width / 2, 26, "Skip : s", BLUE);

	ifstream load;
	load.open("베네치아_스토리.txt");
	if (load.is_open())
	{
		Clock clock;
		clock.SetTime(500);

		string text[10];
		int textCount = 0;
		while (true)
		{
			if (clock.Alarm())
			{
				for (int i = 0; i < 10; i++)
				{
					m_draw.WidthLine(m_sca.width / 3, i + 8, m_sca.width / 3, "  ");
					m_draw.TextMiddle(m_sca.width / 2, i + 8, text[i], BLUE);
				}
				if (textCount < 10)
					getline(load, text[textCount++]);
				else
				{
					for (int i = 0; i < 9; i++)
						text[i] = text[i + 1];
					if (!load.eof())
						getline(load, text[9]);
					else if (text[0] != "  ")
						text[9] = "  ";
					else
						break;
				}
			}
			if (Hit() == 's')
				break;
		}
		load.close();
	}
}

void Interface::ClearTextBox()
{
	m_draw.Rectangle(m_sca.width / 2 - 8, 25, 16, 3, "  ");
}

void Interface::DrawTextBox()
{
	ClearTextBox();
	m_draw.Box(m_sca.width / 2 - 9, 24, 18, 5, BLUE);
}

void Interface::DrawNameInput()
{
	ClearBox();
	m_draw.TextMiddle(m_sca.width / 2, 21, "이름 입력", BLUE);
	DrawTextBox();
}

void Interface::DrawStage(int stage)
{
	ClearBox();
	m_draw.TextMiddle(m_sca.width / 2, 17, "★ " + to_string(stage) + " Stage ★", BLUE);
	Sleep(1000);
	ClearBox();
	DrawTextBox();
}

void Interface::DrawInputWord(string word, bool blind)
{
	if (blind)
	{
		string tmp = word;
		for (int i = 0; i < tmp.length(); i++)
			tmp[i] = '*';
		m_draw.TextMiddle(m_sca.width / 2, 26, tmp, BLUE);
	}
	else
		m_draw.TextMiddle(m_sca.width / 2, 26, word, BLUE);
}

void Interface::DrawRank()
{
	ClearBox();
	ClearStatus();
	DrawRankBox();
	m_draw.WidthLine(1, 8, m_sca.width - 2, "==", BLUE);
	m_draw.TextMiddle(m_sca.width / 3, 10, "Name", BLUE);
	m_draw.TextMiddle(m_sca.width / 2, 10, "Score", BLUE);
	m_draw.TextMiddle(m_sca.width / 3 * 2, 10, "Stage", BLUE);
}

void Interface::DrawRankBox()
{
	m_draw.Box(m_sca.width / 2 - 9, 3, 18, 5, BLUE);
	m_draw.TextMiddle(m_sca.width / 2, 5, "Ranking Box", BLUE);
}

void Interface::DrawRankList(string name, int stage, int score, int index)
{
	m_draw.TextMiddle(m_sca.width / 3, 11 + index * 2, name, BLUE);
	m_draw.TextMiddle(m_sca.width / 2, 11 + index * 2, to_string(score), BLUE);
	m_draw.TextMiddle(m_sca.width / 3 * 2, 11 + index * 2, to_string(stage), BLUE);
}

int Interface::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
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

Interface::~Interface()
{

}