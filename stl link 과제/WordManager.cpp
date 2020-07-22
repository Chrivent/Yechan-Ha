#include "WordManager.h"

WordManager::WordManager()
{
	m_word.assign(GetWordCount(), NULL);
}

int WordManager::GetWordCount()
{
	int wordCount = 0;

	ifstream load;
	load.open("Word.txt");
	if (load.is_open())
	{
		string tmp;
		while (!load.eof())
		{
			load >> tmp;
			wordCount++;
		}
		load.close();
	}

	return wordCount;
}

void WordManager::CreateWord()
{
	Material material;

	Material* matTmp = new Material[GetWordCount()];
	ifstream load;
	load.open("Word.txt");
	if (load.is_open())
	{
		for (int i = 0; i < GetWordCount(); i++)
		{
			string strTmp;
			load >> strTmp;

			matTmp[i].texture = strTmp;
			if (RandBool(3, 2))
				matTmp[i].color = BLUE;
			else
				matTmp[i].color = RandNum(HIGH_GREEN, YELLOW);
		}
		load.close();
	}
	material = matTmp[RandNum(0, GetWordCount() - 1)];

	delete[] matTmp;

	while (true)
	{
		int index = RandNum(0, GetWordCount() - 1);

		list<Word*>::iterator iter = m_word.begin();
		for (int i = 0; i < index; i++)
			++iter;

		if (*iter == NULL)
		{
			*iter = new Word;
			(*iter)->SetMaterial(material);
			(*iter)->Draw();
			return;
		}
	}
}

int WordManager::CorrectWordEvent(string word)
{
	int color;

	for (int i = 0; i < GetWordCount(); i++)
	{
		list<Word*>::iterator iter = m_word.begin();
		for (int j = 0; j < i; j++)
			++iter;

		if (*iter != NULL && (*iter)->SameWord(word))
		{
			color = (*iter)->GetColor();

			(*iter)->Erase();
			delete *iter;
			*iter = NULL;

			return color;
		}
	}
	return NULL;
}

void WordManager::DeleteWholeWord()
{
	for (int i = 0; i < GetWordCount(); i++)
	{
		list<Word*>::iterator iter = m_word.begin();
		for (int j = 0; j < i; j++)
			++iter;

		delete *iter;
		*iter = NULL;
	}
}

void WordManager::FallWord()
{
	for (int i = 0; i < GetWordCount(); i++)
	{
		list<Word*>::iterator iter = m_word.begin();
		for (int j = 0; j < i; j++)
			++iter;

		if (*iter != NULL)
			(*iter)->MoveDown();
	}
}

bool WordManager::TouchFloorEvent(int& life)
{
	bool touch = false;

	for (int i = 0; i < GetWordCount(); i++)
	{
		list<Word*>::iterator iter = m_word.begin();
		for (int j = 0; j < i; j++)
			++iter;

		if (*iter != NULL && (*iter)->CheckTouchFloor())
		{
			delete *iter;
			*iter = NULL;

			life--;
			touch = true;
		}
	}

	return touch;
}

void WordManager::DrawWord()
{
	for (int i = 0; i < GetWordCount(); i++)
	{
		list<Word*>::iterator iter = m_word.begin();
		for (int j = 0; j < i; j++)
			++iter;

		if (*iter != NULL)
			(*iter)->Draw();
	}
}

void WordManager::EraseWord()
{
	for (int i = 0; i < GetWordCount(); i++)
	{
		list<Word*>::iterator iter = m_word.begin();
		for (int j = 0; j < i; j++)
			++iter;

		if (*iter != NULL)
			(*iter)->Erase();
	}
}

WordManager::~WordManager()
{
	DeleteWholeWord();
}