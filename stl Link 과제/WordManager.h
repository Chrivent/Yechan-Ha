#pragma once

#include "Word.h"

class WordManager
{
private:
	list<Word*> m_word;

public:
	WordManager();

	int GetWordCount();
	void CreateWord();
	int CorrectWordEvent(string word);
	void DeleteWholeWord();
	void FallWord();
	bool TouchFloorEvent(int& life);
	void DrawWord();
	void EraseWord();

	~WordManager();
};