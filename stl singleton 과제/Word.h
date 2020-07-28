#pragma once

#include "mecro.h"

class Word
{
private:
	Draw m_draw;
	Position m_pos;
	Material m_mat;

public:
	Word();

	void SetMaterial(Material material);
	void MoveDown();
	bool CheckTouchFloor();
	void Draw();
	void Erase();
	bool SameWord(string word);
	int GetColor();

	~Word();
};