#pragma once
#pragma comment(lib,"msimg32.lib")

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
#define PURPLE RGB(255, 0, 255)
#define SKYBLUE RGB(0, 255, 255)
#define WHITE RGB(255, 255, 255)

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

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
	bool operator != (Transform transform)
	{
		if (*this == transform)
			return false;
		return true;
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

	inline float Pi()
	{
		return atan(1) * 4;
	}

	inline SYSTEMTIME CurrentTime()
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		return st;
	}

	inline float DiagonalLength(Scale scale)
	{
		return sqrt(pow(scale.width, 2) + pow(scale.height, 2));
	}

	inline float PositionAngle(Position position1, Position position2)
	{
		Scale scale;
		float angle;

		if (position1.x <= position2.x)
		{
			scale.width = position2.x - position1.x;
			if (position1.y <= position2.y)
			{
				scale.height = position2.y - position1.y;
				angle = acos(scale.width / DiagonalLength(scale)) * (180 / Pi());
			}
			else
			{
				scale.height = position1.y - position2.y;
				angle = acos(scale.height / DiagonalLength(scale)) * (180 / Pi()) + 270;
			}
		}
		else
		{
			scale.width = position1.x - position2.x;
			if (position1.y <= position2.y)
			{
				scale.height = position2.y - position1.y;
				angle = acos(scale.height / DiagonalLength(scale)) * (180 / Pi()) + 90;
			}
			else
			{
				scale.height = position1.y - position2.y;
				angle = acos(scale.width / DiagonalLength(scale)) * (180 / Pi()) + 180;
			}
		}

		return angle;
	}

	inline Position MousePosition(LPARAM lParam)
	{
		return { LOWORD(lParam), HIWORD(lParam) };
	}

	inline Position AnglePosition(Position position, int length, int angle)
	{
		return { int(position.x + length * cos(angle * Pi() / 180)), int(position.y + length * sin(angle * Pi() / 180)) };
	}

	inline Scale BitmapScale(HDC hdc, LPCSTR fileName)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		BITMAP bitmap;
		GetObject(myBitmap, sizeof(BITMAP), (LPVOID)&bitmap);

		Scale scale;
		scale.width = (int)bitmap.bmWidth;
		scale.height = (int)bitmap.bmHeight;

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);

		return scale;
	}

	inline Scale ScreenScale()
	{
		return { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	}

	inline void SetWindowTransform(HWND hWnd, Transform transform)
	{
		SetWindowPos(hWnd, NULL, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, 0);
	}

	inline void SetClientTransform(HWND hWnd, Transform transform)
	{
		SetWindowPos(hWnd, NULL, transform.position.x, transform.position.y, transform.scale.width + GetSystemMetrics(SM_CXFRAME) * 4, transform.scale.height + GetSystemMetrics(SM_CYFRAME) * 4 + GetSystemMetrics(SM_CYCAPTION), 0);
	}

	inline Transform GetWindowTransform(HWND hWnd)
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);

		return { { rect.left, rect.top }, { rect.right - rect.left, rect.bottom - rect.top } };
	}

	inline Transform GetClientTransform(HWND hWnd)
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return { { rect.left, rect.top }, { rect.right - rect.left, rect.bottom - rect.top } };
	}

	inline bool CheckPositionIsInTransform(Transform transform, Position position)
	{
		RECT rect;
		rect.left = transform.position.x;
		rect.top = transform.position.y;
		rect.right = transform.position.x + transform.scale.width;
		rect.bottom = transform.position.y + transform.scale.height;

		POINT point;
		point.x = position.x;
		point.y = position.y;

		if (PtInRect(&rect, point))
			return true;
		return false;
	}

	inline bool CheckTransformIsIntersect(Transform transform1, Transform transform2)
	{
		RECT tmp, rect1, rect2;

		rect1.left = transform1.position.x;
		rect1.top = transform1.position.y;
		rect1.right = transform1.position.x + transform1.scale.width;
		rect1.bottom = transform1.position.y + transform1.scale.height;

		rect2.left = transform2.position.x;
		rect2.top = transform2.position.y;
		rect2.right = transform2.position.x + transform2.scale.width;
		rect2.bottom = transform2.position.y + transform2.scale.height;

		if (IntersectRect(&tmp, &rect1, &rect2))
			return true;
		return false;
	}

	inline void DrawLine(HDC hdc, Position position1, Position position2, int thickness, COLORREF color = BLACK)
	{
		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		MoveToEx(hdc, position1.x, position1.y, NULL);
		LineTo(hdc, position2.x, position2.y);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	inline void DrawRectangle(HDC hdc, Transform transform, COLORREF color = BLACK)
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

	inline void DrawRectangleEmpty(HDC hdc, Transform transform, int thickness, COLORREF color = BLACK)
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

	inline void DrawRectangleCustom(HDC hdc, Transform transform, int thickness, COLORREF faceColor, COLORREF edgeColor)
	{
		HBRUSH myBrush = CreateSolidBrush(faceColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x + thickness / 2, transform.position.y + thickness / 2, transform.position.x + transform.scale.width - thickness / 2, transform.position.y + transform.scale.height - thickness / 2);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	inline void DrawEllipse(HDC hdc, Transform transform, COLORREF color = BLACK)
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

	inline void DrawEllipseEmpty(HDC hdc, Transform transform, int thickness, COLORREF color = BLACK)
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

	inline 	void DrawEllipseCustom(HDC hdc, Transform transform, int thickness, COLORREF faceColor, COLORREF edgeColor)
	{
		HBRUSH myBrush = CreateSolidBrush(faceColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Ellipse(hdc, transform.position.x + thickness / 2, transform.position.y + thickness / 2, transform.position.x + transform.scale.width - thickness / 2, transform.position.y + transform.scale.height - thickness / 2);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	inline void DrawTextOut(HDC hdc, Transform transform, LPCSTR text, COLORREF color = BLACK)
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

	inline void DrawBitmap(HDC hdc, Transform transform, LPCSTR fileName)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		Scale bitmapScale = BitmapScale(hdc, fileName);
		StretchBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, 0, 0, bitmapScale.width, bitmapScale.height, SRCCOPY);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	inline void DrawBitmapTransparent(HDC hdc, Transform transform, LPCSTR fileName, COLORREF color = PURPLE)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		Scale bitmapScale = BitmapScale(hdc, fileName);
		TransparentBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, 0, 0, bitmapScale.width, bitmapScale.height, color);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	inline void DrawBitmapPart(HDC hdc, Transform transform, LPCSTR fileName, int widthCell, int heightCell, int index)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		if (index >= widthCell * heightCell)
			index = widthCell * heightCell - 1;

		Scale bitmapScale = BitmapScale(hdc, fileName);
		StretchBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, bitmapScale.width / widthCell * (index % widthCell), bitmapScale.height / heightCell * (index / heightCell), bitmapScale.width / widthCell, bitmapScale.height / heightCell, SRCCOPY);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	inline void DrawBitmapPartTransparent(HDC hdc, Transform transform, LPCSTR fileName, int widthCell, int heightCell, int index, COLORREF color = PURPLE)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		if (index >= widthCell * heightCell)
			index = widthCell * heightCell - 1;

		Scale bitmapScale = BitmapScale(hdc, fileName);
		TransparentBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, bitmapScale.width / widthCell * (index % widthCell), bitmapScale.height / heightCell * (index / heightCell), bitmapScale.width / widthCell, bitmapScale.height / heightCell, color);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}
}

using namespace mecro;