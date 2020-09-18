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

#define BLACK RGB(0, 0, 0)
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define YELLOW RGB(255, 255, 0)
#define BLUE RGB(0, 0, 255)
#define PUPPLE RGB(255, 0, 255)
#define SKYBLUE RGB(0, 255, 255)
#define WHITE RGB(255, 255, 255)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Hello, World!");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

struct Position
{
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

struct Scale
{
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

struct Transform
{
	Position position;
	Scale scale;

	bool operator == (Transform transform)
	{
		if (position == transform.position && scale == transform.scale)
			return true;
		return false;
	}

	void MoveLeft(int distance = 1)
	{
		position.x -= distance;
	}

	void MoveRight(int distance = 1)
	{
		position.x += distance;
	}

	void MoveUp(int distance = 1)
	{
		position.y -= distance;
	}

	void MoveDown(int distance = 1)
	{
		position.y += distance;
	}
};

namespace mecro
{
	using namespace std;

	void DrawRectangle(HDC hdc, Position position, int width, int height, COLORREF color)
	{
		for (int x = position.x; x < position.x + width; x++)
		{
			for (int y = position.y; y < position.y + height; y++)
				SetPixel(hdc, x, y, color);
		}
	}

	void DrawRectangleEmpty(HDC hdc, Position position, int width, int height, COLORREF color)
	{
		for (int x = position.x; x < position.x + width; x++)
		{
			SetPixel(hdc, x, position.y, color);
			SetPixel(hdc, x, position.y + height - 1, color);
		}
		for (int y = position.y; y < position.y + height; y++)
		{
			SetPixel(hdc, position.x, y, color);
			SetPixel(hdc, position.x + width - 1, y, color);
		}
	}

	void DrawEllipse(HDC hdc, Position position, int width, int height, COLORREF color)
	{
		for (int x = position.x; x < position.x + width; x++)
		{
			for (int y = position.y; y < position.y + height; y++)
			{
				int a = width / 2;
				int b = height / 2;

				float tmp = pow(x - (position.x + a), 2) / pow(a, 2) + pow(y - (position.y + b), 2) / pow(b, 2);

				if (tmp <= 1)
					SetPixel(hdc, x, y, color);
			}
		}
	}

	void DrawEllipseEmpty(HDC hdc, Position position, int width, int height, COLORREF color)
	{
		for (int x = position.x; x < position.x + width; x++)
		{
			for (int y = position.y; y < position.y + height; y++)
			{
				int a = width / 2;
				int b = height / 2;

				float tmp1 = pow(x - (position.x + a), 2) / pow(a, 2) + pow(y - (position.y + b), 2) / pow(b, 2);
				float tmp2 = pow(x - (position.x + a), 2) / pow(a - 1, 2) + pow(y - (position.y + b), 2) / pow(b - 1, 2);

				if (tmp1 <= 1 && tmp2 >= 1)
					SetPixel(hdc, x, y, color);
			}
		}
	}

	Position MousePosition(LPARAM lParam)
	{
		return { LOWORD(lParam), HIWORD(lParam) };
	}
}

using namespace mecro;