#pragma once

#include "Interface.h"

class Rank
{
private:
	Interface m_inf;
	
public:
	Rank();

	void Save(string name, int stage, int score);
	void ShowList();
	void SortList(string* name, int* stage, int* score);
	int ListCount();

	~Rank();
};