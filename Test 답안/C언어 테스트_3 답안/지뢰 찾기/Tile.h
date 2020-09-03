#pragma once

#include "Mine.h"

class Tile : public Object
{
private:
	bool unpack;
	bool plag;
	bool questionMark;

public:
	Tile();

	void DrawTile(Mine* mine, int mineCount);
	void Unpack();
	int MineCountAround(Mine* mine, int mineCount);
	bool CheckUnpack();
	bool CheckPlag();
	bool CheckQuestionMark();
	void SetPlag();
	void DeletePlag();
	void SetQuestionMark();
	void DeleteQuestionMark();
};