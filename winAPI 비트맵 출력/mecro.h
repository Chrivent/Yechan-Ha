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

struct Object
{
	Transform transform;

	virtual void Draw(HDC hdc) = 0;
};

namespace mecro
{
	using namespace std;

	int RandNum(int min, int max)
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

	bool RandBool(int denominator, int numerator)
	{
		int randNum = RandNum(1, denominator);

		if (randNum >= 1 && randNum <= numerator)
			return true;
		return false;
	}

	float Pi()
	{
		return atan(1) * 4;
	}

	Scale BitmapScale(int bitmapID)
	{
		HBITMAP hBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(bitmapID));

		BITMAP bitmap;
		GetObject(hBitmap, sizeof(BITMAP), (LPVOID)&bitmap);

		Scale scale;
		scale.width = (int)bitmap.bmWidth;
		scale.height = (int)bitmap.bmHeight;

		return scale;
	}

	void DrawLine(HDC hdc, Position position1, Position position2, int thickness, COLORREF color = BLACK)
	{
		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		MoveToEx(hdc, position1.x, position1.y, NULL);
		LineTo(hdc, position2.x, position2.y);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawRectangle(HDC hdc, Transform transform, COLORREF color = BLACK)
	{
		HBRUSH myBrush = CreateSolidBrush(color);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, 1, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawRectangleEmpty(HDC hdc, Transform transform, int thickness, COLORREF color = BLACK)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x + thickness / 2, transform.position.y + thickness / 2, transform.position.x + transform.scale.width - thickness / 2, transform.position.y + transform.scale.height - thickness / 2);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawRectangleCustom(HDC hdc, Transform transform, int thickness, COLORREF faceColor, COLORREF edgeColor)
	{
		HBRUSH myBrush = CreateSolidBrush(faceColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawEllipse(HDC hdc, Transform transform, COLORREF color = BLACK)
	{
		HBRUSH myBrush = CreateSolidBrush(color);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, 1, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Ellipse(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawEllipseEmpty(HDC hdc, Transform transform, int thickness, COLORREF color = BLACK)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Ellipse(hdc, transform.position.x + thickness / 2, transform.position.y + thickness / 2, transform.position.x + transform.scale.width - thickness / 2, transform.position.y + transform.scale.height - thickness / 2);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawEllipseCustom(HDC hdc, Transform transform, int thickness, COLORREF faceColor, COLORREF edgeColor)
	{
		HBRUSH myBrush = CreateSolidBrush(faceColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Ellipse(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawTextOut(HDC hdc, Transform transform, LPCWSTR text, COLORREF color = BLACK)
	{
		int width = transform.scale.width / lstrlen(text);

		HFONT myFont = CreateFont(transform.scale.height, width, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("±Ã¼­"));
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

		SetTextColor(hdc, color);
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, transform.position.x, transform.position.y, text, lstrlen(text));

		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}

	void DrawBitmap(HDC hdc, Position position, int bitmapID, Scale scale = { 1, 1 })
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(bitmapID));
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		Scale bitmapScale = BitmapScale(bitmapID);
		StretchBlt(hdc, position.x, position.y, bitmapScale.width * scale.width, bitmapScale.height * scale.height, MemDC, 0, 0, bitmapScale.width, bitmapScale.height, SRCCOPY);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	Position MousePosition(LPARAM lParam)
	{
		return { LOWORD(lParam), HIWORD(lParam) };
	}

	Position AnglePosition(Position position, int length, int angle)
	{
		return { int(position.x + length * cos(angle * Pi() / 180)), int(position.y + length * sin(angle * Pi() / 180)) };
	}
}

using namespace mecro;