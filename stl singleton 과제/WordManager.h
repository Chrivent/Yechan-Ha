#pragma once

#include "Word.h"
#include "Singleton.h"

class WordManager : public Singleton<WordManager>
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