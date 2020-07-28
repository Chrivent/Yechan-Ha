#pragma once

#include "Interface.h"
#include "WordManager.h"
#include "Rank.h"

#define WORD_MAX 100

class Play
{
private:
	Interface m_inf;
	int m_life;
	int m_score;
	string m_name;
	int m_stage;
	WordManager* m_wordMan;
	Rank m_rank;

public:
	Play();

	void SetName();
	void ResetStatus();
	int GetLife();
	int GetScore();
	string GetName();
	void Start();
	bool Playing();

	~Play();
};