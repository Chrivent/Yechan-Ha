#include "mecro.h"
#include "resource.h"

class Bitmap : public Object
{
private:
	int id;

public:
	Bitmap(int id)
	{
		this->id = id;
	}

	void Draw(HDC hdc)
	{
		DrawBitmap(hdc, transform.position, id);
	}

	bool CheckPositionIsInBitmap(Position position)
	{
		Position positionLU = transform.position;
		Position positionRD = { transform.position.x + BitmapScale(id).width, transform.position.y + BitmapScale(id).height };

		if (position >= positionLU && position <= positionRD)
			return true;
		return false;
	}

	int GetID()
	{
		return id;
	}
};

LPCWSTR GetBitmapName(int id)
{
	if (id == IDB_BITMAP1)
		return TEXT("호랑이");
	else if (id == IDB_BITMAP2)
		return TEXT("오리");
	else if (id == IDB_BITMAP3)
		return TEXT("코끼리");
	else if (id == IDB_BITMAP4)
		return TEXT("소");
	else if (id == IDB_BITMAP5)
		return TEXT("말");
	else if (id == IDB_BITMAP6)
		return TEXT("고양이");
	else if (id == IDB_BITMAP7)
		return TEXT("원숭이");
	else if (id == IDB_BITMAP8)
		return TEXT("개구리");
	else if (id == IDB_BITMAP9)
		return TEXT("닭");
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;

	static Bitmap* bitmap[9];

	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowPos(hWnd, NULL, 0, 0, 1600, 900, 0);

		for (int i = 0; i < 9; i++)
		{
			bitmap[i] = new Bitmap(IDB_BITMAP1 + i);

			if (i < 5)
			{
				bitmap[i]->transform.position.x = i * 200 + 100;
				bitmap[i]->transform.position.y = 100;
			}
			else
			{
				bitmap[i]->transform.position.x = i * 200 - 800;
				bitmap[i]->transform.position.y = 400;
			}
		}

		return 0;

	case WM_DESTROY:
		for (int i = 0; i < 9; i++)
		{
			delete bitmap[i];
			bitmap[i] = NULL;
		}

		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		for (int i = 0; i < 9; i++)
		{
			if (bitmap[i]->CheckPositionIsInBitmap(MousePosition(lParam)))
				MessageBox(hWnd, GetBitmapName(bitmap[i]->GetID()), TEXT("메세지 박스"), MB_OK);
		}
		
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < 9; i++)
			bitmap[i]->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}