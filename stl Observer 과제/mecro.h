#pragma once

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<crtdbg.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<list>

#define BLACK 0x0000
#define DARK_BLUE 0x0001
#define GREEN 0x0002
#define BLUE_GREEN 0x0003
#define BLOOD 0x0004
#define PUPPLE 0x0005
#define GOLD 0x0006
#define ORIGINAL 0x0007
#define GRAY 0x0008
#define BLUE 0x0009
#define HIGH_GREEN 0x000a
#define SKY_BLUE 0x000b
#define RED 0x000c
#define PLUM 0x000d
#define YELLOW 0x000e

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define ENTER 13
#define ESC 27
#define SPACE 32
#define BACKSPACE 8

namespace mecro
{
	using std::string;
	using std::ofstream;
	using std::ifstream;
	using std::ios;
	using std::cout;
	using std::cin;
	using std::endl;
	using std::to_string;
	using std::fixed;
	using std::setprecision;
	using std::vector;
	using std::list;

	inline void Gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	inline void SetScreenSize(int width, int height)
	{
		system(("mode con: lines=" + to_string(height) + " cols=" + to_string((width * 2) + 1)).c_str());
	}

	inline int RandNum(int min, int max)
	{
		static bool tmp;

		if (tmp != true)
		{
			srand(time(NULL));
			tmp = true;
		}

		while (true)
		{
			int num = rand() % (max + 1);
			if (num >= min)
				return num;
		}
	}

	inline bool RandBool(int denominator, int numerator)
	{
		int randNum = RandNum(1, denominator);

		if (randNum >= 1 && randNum <= numerator)
			return true;
		return false;
	}

	inline int Hit()
	{
		return kbhit() ? getch() : NULL;
	}

	inline void Print(string str, int color = ORIGINAL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << str;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ORIGINAL);
	}

	inline void Print(char cha, int color = ORIGINAL)
	{
		Print(string(1, cha), color);
	}

	inline void Print(int num, int color = ORIGINAL)
	{
		Print(to_string(num), color);
	}

	inline void PrintLine(string str, int color = ORIGINAL)
	{
		Print(str, color);
		cout << endl;
	}

	inline void PrintLine(char cha, int color = ORIGINAL)
	{
		Print(cha, color);
		cout << endl;
	}

	inline void PrintLine(int num, int color = ORIGINAL)
	{
		Print(num, color);
		cout << endl;
	}

	inline void Scan(string& str, int color = ORIGINAL)
	{
		while (true)
		{
			char input = Hit();
			if (input)
			{
				if (input == ENTER)
				{
					cout << endl;
					return;
				}
				else if (input == BACKSPACE)
				{
					if (str.length() > 0)
					{
						Print("\b");
						Print(" ");
						Print("\b");
						str.pop_back();
					}
				}
				else
				{
					Print(input, color);
					str.push_back(input);
				}
			}
		}
	}

	inline void Scan(char& cha, int color = ORIGINAL)
	{
		cha = NULL;
		while (true)
		{
			char input = Hit();
			if (input)
			{
				if (input == ENTER)
				{
					cout << endl;
					return;
				}
				else if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || (input >= '0' && input <= '9'))
				{
					if (cha != NULL)
						Print("\b");
					Print(input, color);
					cha = input;
				}
				else
				{
					if (cha != NULL)
					{
						Print("\b");
						Print(" ");
						Print("\b");
						cha = NULL;
					}
				}
			}
		}
	}

	inline void Scan(int& num, int color = ORIGINAL)
	{
		string str;
		while (true)
		{
			char input = Hit();
			if (input)
			{
				if (input == ENTER)
				{
					num = atoi(str.c_str());
					cout << endl;
					return;
				}
				else if (input == BACKSPACE)
				{
					if (str.length() > 0)
					{
						Print("\b");
						Print(" ");
						Print("\b");
						str.pop_back();
					}
				}
				else if (input >= '0' && input <= '9')
				{
					Print(input, color);
					str.push_back(input);
				}
			}
		}
	}

	inline string InputStr(int color = ORIGINAL)
	{
		string str;
		Scan(str, color);
		return str;
	}

	inline char InputCha(int color = ORIGINAL)
	{
		char cha;
		Scan(cha, color);
		return cha;
	}

	inline int InputNum(int color = ORIGINAL)
	{
		int num;
		Scan(num, color);
		return num;
	}
}

using namespace mecro;

class Position
{
public:
	int x;
	int y;

	Position operator + (Position position)
	{
		Position tmp;
		tmp.x = x + position.x;
		tmp.y = y + position.y;
		return tmp;
	}
	Position operator - (Position position)
	{
		Position tmp;
		tmp.x = x - position.x;
		tmp.y = y - position.y;
		return tmp;
	}
	Position operator * (Position position)
	{
		Position tmp;
		tmp.x = x * position.x;
		tmp.y = y * position.y;
		return tmp;
	}
	Position operator / (Position position)
	{
		Position tmp;
		tmp.x = x / position.x;
		tmp.y = y / position.y;
		return tmp;
	}
	Position operator % (Position position)
	{
		Position tmp;
		tmp.x = x % position.x;
		tmp.y = y % position.y;
		return tmp;
	}

	void operator += (Position position)
	{
		*this = *this + position;
	}
	void operator -= (Position position)
	{
		*this = *this - position;
	}
	void operator *= (Position position)
	{
		*this = *this * position;
	}
	void operator /= (Position position)
	{
		*this = *this / position;
	}
	void operator %= (Position position)
	{
		*this = *this % position;
	}

	void operator ++ ()
	{
		x++;
		y++;
	}
	void operator ++ (int)
	{
		++(*this);
	}

	void operator -- ()
	{
		x--;
		y--;
	}
	void operator -- (int)
	{
		--(*this);
	}

	bool operator == (Position position)
	{
		if (x == position.x && y == position.y)
			return true;
		return false;
	}
	bool operator != (Position position)
	{
		if (*this == position)
			return false;
		return true;
	}

	bool operator > (Position position)
	{
		if (x > position.x && y > position.y)
			return true;
		return false;
	}
	bool operator >= (Position position)
	{
		if (*this > position || *this == position)
			return true;
		return false;
	}

	bool operator < (Position position)
	{
		if (x < position.x && y < position.y)
			return true;
		return false;
	}
	bool operator <= (Position position)
	{
		if (*this < position || *this == position)
			return true;
		return false;
	}
};

class Scale
{
public:
	int width;
	int height;

	Scale operator + (Scale scale)
	{
		Scale tmp;
		tmp.width = width + scale.width;
		tmp.height = height + scale.height;
		return tmp;
	}
	Scale operator - (Scale scale)
	{
		Scale tmp;
		tmp.width = width - scale.width;
		tmp.height = height - scale.height;
		return tmp;
	}
	Scale operator * (Scale scale)
	{
		Scale tmp;
		tmp.width = width * scale.width;
		tmp.height = height * scale.height;
		return tmp;
	}
	Scale operator / (Scale scale)
	{
		Scale tmp;
		tmp.width = width / scale.width;
		tmp.height = height / scale.height;
		return tmp;
	}
	Scale operator % (Scale scale)
	{
		Scale tmp;
		tmp.width = width % scale.width;
		tmp.height = height % scale.height;
		return tmp;
	}

	void operator += (Scale scale)
	{
		*this = *this + scale;
	}
	void operator -= (Scale scale)
	{
		*this = *this - scale;
	}
	void operator *= (Scale scale)
	{
		*this = *this * scale;
	}
	void operator /= (Scale scale)
	{
		*this = *this / scale;
	}
	void operator %= (Scale scale)
	{
		*this = *this % scale;
	}

	void operator ++ ()
	{
		width++;
		height++;
	}
	void operator ++ (int)
	{
		++(*this);
	}

	void operator -- ()
	{
		width--;
		height--;
	}
	void operator -- (int)
	{
		--(*this);
	}

	bool operator == (Scale scale)
	{
		if (width == scale.width && height == scale.height)
			return true;
		return false;
	}
	bool operator != (Scale scale)
	{
		if (*this == scale)
			return false;
		return true;
	}

	bool operator > (Scale scale)
	{
		if (width > scale.width && height > scale.height)
			return true;
		return false;
	}
	bool operator >= (Scale scale)
	{
		if (*this > scale || *this == scale)
			return true;
		return false;
	}

	bool operator < (Scale scale)
	{
		if (width < scale.width && height < scale.height)
			return true;
		return false;
	}
	bool operator <= (Scale scale)
	{
		if (*this < scale || *this == scale)
			return true;
		return false;
	}
};

class Transform
{
public:
	Position position;
	Scale scale;
};

class Material
{
public:
	string texture;
	int color;

	bool operator == (Material material)
	{
		if (texture == material.texture && color == material.color)
			return true;
		return false;
	}
	bool operator != (Material material)
	{
		if (*this == material)
			return false;
		return true;
	}
};

class Draw
{
public:
	void Text(int x, int y, string text, int color = ORIGINAL)
	{
		Gotoxy(x * 2, y);
		Print(text, color);
	}
	void TextMiddle(int x, int y, string text, int color = ORIGINAL)
	{
		Text(x - (int)text.size() / 4, y, text, color);
	}
	void Point(int x, int y, string texture, int color = ORIGINAL)
	{
		Gotoxy(x * 2, y);
		Print(texture, color);
	}
	void WidthLine(int x, int y, int width, string texture, int color = ORIGINAL)
	{
		for (int i = 0; i < width; i++)
			Point(x + i, y, texture, color);
	}
	void HeightLine(int x, int y, int height, string texture, int color = ORIGINAL)
	{
		for (int i = 0; i < height; i++)
			Point(x, y + i, texture, color);
	}
	void Rectangle(int x, int y, int width, int height, string texture, int color = ORIGINAL)
	{
		for (int i = 0; i < height; i++)
			WidthLine(x, y + i, width, texture, color);
	}
	void EmptyRectangle(int x, int y, int width, int height, string texture, int color = ORIGINAL)
	{
		WidthLine(x, y, width, texture, color);
		HeightLine(x, y + 1, height - 2, texture, color);
		HeightLine(x + width - 1, y + 1, height - 2, texture, color);
		WidthLine(x, y + height - 1, width, texture, color);
	}
	void Box(int x, int y, int width, int height, int color = ORIGINAL)
	{
		Point(x, y, "¦£", color);
		WidthLine(x + 1, y, width - 2, "¦¡", color);
		Point(x + width - 1, y, "¦¤", color);
		HeightLine(x, y + 1, height - 2, "¦¢", color);
		HeightLine(x + width - 1, y + 1, height - 2, "¦¢", color);
		Point(x, y + height - 1, "¦¦", color);
		WidthLine(x + 1, y + height - 1, width - 2, "¦¡", color);
		Point(x + width - 1, y + height - 1, "¦¥", color);
	}
	void Grid(int x, int y, int width, int height, int color = ORIGINAL)
	{
		Point(x, y, "¦£", color);
		WidthLine(x + 1, y, width - 2, "¦¨", color);
		Point(x + width - 1, y, "¦¤", color);
		HeightLine(x, y + 1, height - 2, "¦§", color);
		Rectangle(x + 1, y + 1, width, height, "¦«", color);
		HeightLine(x + width - 1, y + 1, height - 2, "¦©", color);
		Point(x, y + height - 1, "¦¦", color);
		WidthLine(x + 1, y + height - 1, width - 2, "¦ª", color);
		Point(x + width - 1, y + height - 1, "¦¥", color);
	}
};

class Clock
{
private:
	int m_clock;
	int m_time;

public:
	Clock() { m_clock = clock(); m_time = 1000; }

	void SetTime(int time) { m_time = time; }
	bool Alarm()
	{
		int tmp = clock();
		if (tmp - m_clock >= m_time)
		{
			m_clock = tmp;
			return true;
		}
		return false;
	}
	int GetTime() { return m_time; }
};

class StopWatch
{
private:
	Clock* m_clock;
	int m_time;

public:
	StopWatch() { m_clock = NULL; m_time = 1000; }

	void SetTime(int time) { m_time = time; }
	void Start()
	{
		if (m_clock != NULL)
		{
			delete m_clock;
			m_clock = NULL;
		}
		m_clock = new Clock;
		m_clock->SetTime(m_time);
	}
	bool Stop()
	{
		if (m_clock != NULL && m_clock->Alarm())
		{
			delete m_clock;
			m_clock = NULL;
			return true;
		}
		return false;
	}
	int GetTime() { return m_time; }

	~StopWatch()
	{
		if (m_clock != NULL)
		{
			delete m_clock;
			m_clock = NULL;
		}
	}
};