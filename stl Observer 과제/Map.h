#pragma once

#include "mecro.h"

enum HAND
{
	HAND_SCISSORS = 1,
	HAND_ROCK,
	HAND_PAPER
};

class Map
{
private:
	Draw m_draw;
	Scale m_scale;

public:
	Map();

	void DrawBox();
	void EraseBoxInner();
	void DrawMain();
	void DrawPlay();
	void DrawDongeon();
	void DrawShop();
	void DrawSlot(int num, bool saved, int slotCount);
	void DrawSaved();
	void DrawNoData();
	void DrawLoaded();
	void DrawStage();
	void DrawSelectWeapon(int gold, string type);
	void DrawSelectPage(int y);
	void DrawHand(int playerHand, int enemyHand, string pl_result, string en_result);
	void DrawMatchResult(string name, int getExp);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	Scale GetScale();

	~Map();
};

