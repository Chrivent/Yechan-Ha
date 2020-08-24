#include "Rank.h"

Rank::Rank()
{

}

void Rank::Save(string name, int stage, int score)
{
	ofstream save;
	save.open("Rank.txt", ios::app);

	if (save.is_open())
	{
		save << name << " " << to_string(stage) << " " << to_string(score) << endl;
		save.close();
	}
}

void Rank::ShowList()
{
	string* name = new string[ListCount()];
	int* stage = new int[ListCount()];
	int* score = new int[ListCount()];

	ifstream load;
	load.open("Rank.txt");

	if (load.is_open())
	{
		for (int i = 0; i < ListCount(); i++)
		{
			load >> name[i];
			load >> stage[i];
			load >> score[i];
		}

		SortList(name, stage, score);

		m_inf.DrawRank();
		for (int i = 0; i < 10; i++)
			m_inf.DrawRankList(name[i], stage[i], score[i], i);

		load.close();
	}

	delete[] name;
	delete[] stage;
	delete[] score;
}

void Rank::SortList(string* name, int* stage, int* score)
{
	for (int j = 0; j < ListCount() - 1; j++)
	{
		for (int i = j + 1; i < ListCount(); i++)
		{
			if (score[j] < score[i])
			{
				string tmpName;
				int tmpStage;
				int tmpScore;

				tmpName = name[j];
				tmpStage = stage[j];
				tmpScore = score[j];

				name[j] = name[i];
				stage[j] = stage[i];
				score[j] = score[i];

				name[i] = tmpName;
				stage[i] = tmpStage;
				score[i] = tmpScore;
			}
		}
	}
}

int Rank::ListCount()
{
	int count = 0;

	ifstream load;
	load.open("Rank.txt");

	if (load.is_open())
	{
		while (!load.eof())
		{
			string name;
			int stage;
			int score;

			load >> name;
			load >> stage;
			load >> score;

			count++;
		}

		load.close();
	}

	return --count;
}

Rank::~Rank()
{

}