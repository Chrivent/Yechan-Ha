#include "mecro.h"

class Character : public Object
{
private:
	int index;
	int direction;
	bool moving;

public:
	Character()
	{
		index = 0;
		direction = DOWN;
		moving = false;
	}

	void Move(int direction)
	{
		moving = true;

		if (this->direction != direction)
		{
			this->direction = direction;
			Update();
		}

		switch (direction)
		{
		case LEFT:
			transform.MoveLeft(10);
			break;

		case RIGHT:
			transform.MoveRight(10);
			break;

		case UP:
			transform.MoveUp(10);
			break;

		case DOWN:
			transform.MoveDown(10);
			break;

		default:
			break;
		}
	}

	void Stop()
	{
		switch (direction)
		{
		case LEFT:
			index = 8;
			break;

		case RIGHT:
			index = 12;
			break;

		case UP:
			index = 4;
			break;

		case DOWN:
			index = 0;
			break;

		default:
			break;
		}

		moving = false;
	}

	void Update()
	{
		if (moving == true)
		{
			switch (direction)
			{
			case LEFT:
				if (index >= 8 && index < 11)
					index++;
				else
					index = 8;
				break;

			case RIGHT:
				if (index >= 12 && index < 15)
					index++;
				else
					index = 12;
				break;

			case UP:
				if (index >= 4 && index < 7)
					index++;
				else
					index = 4;
				break;

			case DOWN:
				if (index >= 0 && index < 3)
					index++;
				else
					index = 0;
				break;

			default:
				break;
			}
		}
	}

	void Draw(HDC hdc)
	{
		DrawBitmapPartTransparent(hdc, transform, TEXT("image.bmp"), 4, 4, index);
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;

	static Character character;
	static int direction;
	static int index;

	switch (iMessage)
	{
	case WM_CREATE:
		SetWindowTransform(hWnd, { { 0, 0 }, { 1280, 720 } });

		SetTimer(hWnd, 1, 1000, NULL);
		SetTimer(hWnd, 2, 33, NULL);

		SetTimer(hWnd, 3, 200, NULL);

		character.transform.position = { 100, 100 };
		character.transform.scale = BitmapScale(TEXT("image.bmp"));
		character.transform.scale /= { 3, 3 };

		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);

		PostQuitMessage(0);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GetLocalTime(&st);
			break;

		case 2:
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case 3:
			character.Update();
			break;

		default:
			break;
		}

		if (GetKeyState(VK_LEFT) & 0x8000)
			character.Move(LEFT);
		else if (GetKeyState(VK_RIGHT) & 0x8000)
			character.Move(RIGHT);
		else if (GetKeyState(VK_UP) & 0x8000)
			character.Move(UP);
		else if (GetKeyState(VK_DOWN) & 0x8000)
			character.Move(DOWN);

		return 0;

	case WM_KEYUP:
		if (wParam == VK_LEFT || wParam == VK_RIGHT || wParam == VK_UP || wParam == VK_DOWN)
			character.Stop();

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		character.Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}