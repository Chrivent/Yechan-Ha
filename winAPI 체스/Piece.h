#pragma once

#include "Tile.h"

class Piece : public Object
{
protected:
	int type;
	bool selected;
	bool moved;
	bool promotioned;

public:
	Piece();

	void SetType(int type);
	int GetType();
	bool CheckSelected();
	void Select();
	void Unselect();
	void Moved();
	void Promotioned();
	bool CheckPromotioned();
	void GetBaseTileIndex(Tile tile[8][8], int& y, int& x);

	virtual void SetPattern(Tile tile[8][8]) = 0;
};