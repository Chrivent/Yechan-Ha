#include "Venice.h"

Venice::Venice()
{

}

void Venice::Run()
{
	m_inf.ChangeScreenSize();
	m_inf.DrawBox();

	while (true)
	{
		m_inf.DrawMainMenu();
		m_inf.DrawStatus(m_pl.GetLife(), m_pl.GetScore(), m_pl.GetName());

		switch (m_inf.MenuSelectCursor(3, 3, 25, 14))
		{
		case 1:
			m_inf.ShowStory();
			m_pl.SetName();
			m_pl.Start();
			break;
		case 2:
			m_rank.ShowList();
			getch();
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

Venice::~Venice()
{

}