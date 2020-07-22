#pragma once

#include "mecro.h"

class Interface
{
private:
	Draw m_draw;
	Scale m_sca;

public:
	Interface();

	void ChangeScreenSize();
	void ClearBox();
	void DrawMainMenu();
	void DrawBox();
	void ClearStatus();
	void DrawStatus(int life, int score, string name);
	void ShowStory();
	void ClearTextBox();
	void DrawTextBox();
	void DrawNameInput();
	void DrawStage(int stage);
	void DrawInputWord(string word, bool blind);
	void DrawRank();
	void DrawRankBox();
	void DrawRankList(string name, int stage, int score, int index);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);

	~Interface();
};