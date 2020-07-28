#pragma once

#include "Interface.h"
#include "Play.h"

class Venice
{
private:
	Interface m_inf;
	Play m_pl;
	Rank m_rank;

public:
	Venice();

	void Run();

	~Venice();
};