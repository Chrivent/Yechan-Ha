#include "Play.h"

Play::Play()
{
	m_wordMan = WordManager::GetInstance();
	ResetStatus();
}

void Play::ResetStatus()
{
	m_life = 9;
	m_score = 0;
	m_name = "? ? ?";
	m_stage = 1;
}

void Play::SetName()
{
	m_inf.DrawNameInput();
	Gotoxy(65, 26);
	m_name = InputStr(BLUE);
}

int Play::GetLife()
{
	return m_life;
}

int Play::GetScore()
{
	return m_score;
}

string Play::GetName()
{
	return m_name;
}

void Play::Start()
{
	while (true)
	{
		m_inf.DrawStatus(m_life, m_score, m_name);
		m_inf.DrawStage(m_stage);

		if (Playing())
			m_stage++;
		else
		{
			m_rank.Save(m_name, m_stage, m_score);
			ResetStatus();
			return;
		}

		m_life = 9;
	}
}

bool Play::Playing()
{
	Clock fallClock;
	Clock createClock;

	fallClock.SetTime(1000 / m_stage);
	createClock.SetTime(10000 / (m_stage * 2));

	int scoreMax = m_stage * (m_stage + 1) * 500;

	StopWatch stopWatch;
	stopWatch.SetTime(10000);

	bool stop = false;
	bool blind = false;

	string word;
	m_wordMan->CreateWord();
	while (true)
	{
		if (stopWatch.Stop())
		{
			fallClock.SetTime(1000 / m_stage);
			createClock.SetTime(10000 / (m_stage * 2));
			stop = false;
			blind = false;
		}

		if (fallClock.Alarm() && !stop)
		{
			m_wordMan->EraseWord();
			m_wordMan->FallWord();
			if (m_wordMan->TouchFloorEvent(m_life))
				m_inf.DrawStatus(m_life, m_score, m_name);
			m_wordMan->DrawWord();

			m_inf.DrawTextBox();
			m_inf.DrawInputWord(word, blind);
		}

		if (createClock.Alarm() && !stop)
			m_wordMan->CreateWord();

		char input = Hit();
		if (input)
		{
			m_inf.ClearTextBox();

			if (input == ENTER)
			{
				int color = m_wordMan->CorrectWordEvent(word);

				if (color)
				{
					m_score += 100;
					m_inf.DrawStatus(m_life, m_score, m_name);

					switch (color)
					{
					case HIGH_GREEN:
						fallClock.SetTime(500 / m_stage);
						createClock.SetTime(5000 / (m_stage * 2));
						stopWatch.Start();
						break;
					case SKY_BLUE:
						fallClock.SetTime(2000 / m_stage);
						createClock.SetTime(20000 / (m_stage * 2));
						stopWatch.Start();
						break;
					case RED:
						stop = true;
						stopWatch.Start();
						break;
					case PLUM:
						m_wordMan->EraseWord();
						m_wordMan->DeleteWholeWord();
						break;
					case YELLOW:
						blind = true;
						stopWatch.Start();
						break;
					default:
						break;
					}
				}
				word = "";
			}
			else if (input == BACKSPACE)
			{
				if (word.length() > 0)
					word.pop_back();
			}
			else
				word.push_back(input);

			m_inf.DrawInputWord(word, blind);
		}

		if (m_score >= scoreMax)
		{
			m_wordMan->DeleteWholeWord();
			return true;
		}

		if (m_life <= 0)
		{
			m_wordMan->DeleteWholeWord();
			return false;
		}
	}
}

Play::~Play()
{

}