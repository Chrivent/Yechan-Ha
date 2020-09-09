#pragma once

#include "Mine.h"
#include "Tile.h"
#include "Cursor.h"

class Minesweeper
{
private:
	int height;
	int width;
	int mineCount;
	bool useQuestionMark;
	string level;

	Mine* mine;
	Tile* tile;
	Cursor cursor;

public:
	Minesweeper();

	void Init();
	void Load();
	void DrawMap();
	void DrawMineCount();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void EnterEvent();
	void UnpackTile(Position position);
	bool CheckPositionIsMine(Position position);
	bool CheckPositionIsUnpackTile(Position position);
	bool CheckPositionIsNumberTile(Position position);
	bool CheckPositionIsInMap(Position position);
	void SpaceEvent();
	void Option(bool& playing);
	void SetLevel();
	bool CheckFindAllMine();
	int PackTileCount();
	int PlagTileCount();
	int TileCount();
	void Release();

	~Minesweeper();
};