#include "mecro.h"

struct Object
{
	Transform transform;
	COLORREF color;
};

void SortCursorPosition(Object& cursor, Object box)
{
	if (cursor.transform.position.x <= box.transform.position.x)
		cursor.transform.position.x = box.transform.position.x + 1;
	else if (cursor.transform.position.x >= box.transform.position.x + box.transform.scale.width - cursor.transform.scale.width)
		cursor.transform.position.x = box.transform.position.x + box.transform.scale.width - cursor.transform.scale.width - 1;

	if (cursor.transform.position.y <= box.transform.position.y)
		cursor.transform.position.y = box.transform.position.y + 1;
	else if (cursor.transform.position.y >= box.transform.position.y + box.transform.scale.height - cursor.transform.scale.height)
		cursor.transform.position.y = box.transform.position.y + box.transform.scale.height - cursor.transform.scale.height - 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static Object cursor;
	cursor.transform.scale = { 70, 70 };
	cursor.color = RED;

	static Object box;
	box.transform.scale = { 400, 400 };
	box.color = BLUE;

	static bool circleCursor = true;

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		cursor.transform.position = { MousePosition(lParam).x - cursor.transform.scale.width / 2, MousePosition(lParam).y - cursor.transform.scale.height / 2 };
		SortCursorPosition(cursor, box);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			box.transform.MoveLeft(10);
			break;
		case VK_RIGHT:
			box.transform.MoveRight(10);
			break;
		case VK_UP:
			box.transform.MoveUp(10);
			break;
		case VK_DOWN:
			box.transform.MoveDown(10);
			break;
		case VK_ESCAPE:
			if (MessageBox(hWnd, TEXT("변형"), TEXT("알림"), MB_YESNO) == IDYES)
				circleCursor = circleCursor ? false : true;
			break;
		default:
			break;
		}
		SortCursorPosition(cursor, box);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (circleCursor)
			DrawEllipseEmpty(hdc, cursor.transform.position, cursor.transform.scale.width, cursor.transform.scale.height, cursor.color);
		else
			DrawRectangleEmpty(hdc, cursor.transform.position, cursor.transform.scale.width, cursor.transform.scale.height, cursor.color);

		DrawRectangleEmpty(hdc, box.transform.position, box.transform.scale.width, box.transform.scale.height, box.color);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}