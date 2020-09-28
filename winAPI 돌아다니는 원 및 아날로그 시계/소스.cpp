#include "mecro.h"

Position RandLocalPosition(int distance)
{
	Position localPosition;

	localPosition.x = RandNum(0, distance) * (RandBool(2, 1) ? -1 : 1);
	localPosition.y = sqrt(pow(distance, 2) - pow(localPosition.x, 2)) * (RandBool(2, 1) ? -1 : 1);

	return localPosition;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;

	static Scale scale;

	static Object background;
	static Object ball;
	static Position localPosition;
	static int distance;
	static Object timeText;
	static TCHAR time[256];
	static Object clockCircle;
	static Line secondLine;
	static Line minuteLine;
	static Line hourLine;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SetTimer(hWnd, 2, 33, NULL);

		scale = { 1, 1 };

		background.transform.position = { scale.width * 5, scale.height * 5 };
		background.transform.scale = { scale.width * 800, scale.height * 450 };
		background.color = RED;

		ball.transform.position = { background.transform.position.x + background.transform.scale.width / 2, 150 };
		ball.transform.scale = { background.transform.scale.width / 20, (background.transform.scale.height / 45) * 4 };
		ball.color = BLUE;

		distance = ( background.transform.position.x + background.transform.position.y ) / 2;
		localPosition = RandLocalPosition(distance);

		timeText.transform.position = { background.transform.position.x + background.transform.scale.width / 4, background.transform.position.y + (background.transform.scale.height / 14) * 13 };
		timeText.transform.scale = { background.transform.scale.width / 2, background.transform.scale.height / 15 };
		timeText.color = GREEN;

		clockCircle.transform.position = { background.transform.position.x + background.transform.scale.width / 4, background.transform.position.y + background.transform.scale.height / 40 };
		clockCircle.transform.scale = { background.transform.scale.width / 2, background.transform.scale.width / 2 };
		clockCircle.color = SKYBLUE;

		secondLine.color = BLUE;
		minuteLine.color = BLUE;
		hourLine.color = BLUE;

		SendMessage(hWnd, WM_TIMER, 1, lParam);

		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);

		PostQuitMessage(0);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			GetLocalTime(&st);

			wsprintf(time, TEXT("%d %d/%d %d : %d : %d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			secondLine.position1 = { clockCircle.transform.position.x + clockCircle.transform.scale.width / 2, clockCircle.transform.position.y + clockCircle.transform.scale.height / 2 };
			secondLine.position2 = { int(secondLine.position1.x + 180 * cos((270 + 6 * st.wSecond) * 3.141592 / 180)), int(secondLine.position1.y + 180 * sin((270 + 6 * st.wSecond) * 3.141592 / 180)) };

			minuteLine.position1 = { clockCircle.transform.position.x + clockCircle.transform.scale.width / 2, clockCircle.transform.position.y + clockCircle.transform.scale.height / 2 };
			minuteLine.position2 = { int(minuteLine.position1.x + 150 * cos((270 + 6 * st.wMinute + st.wSecond / 10) * 3.141592 / 180)), int(minuteLine.position1.y + 150 * sin((270 + 6 * st.wMinute + st.wSecond / 10) * 3.141592 / 180)) };

			hourLine.position1 = { clockCircle.transform.position.x + clockCircle.transform.scale.width / 2, clockCircle.transform.position.y + clockCircle.transform.scale.height / 2 };
			hourLine.position2 = { int(hourLine.position1.x + 120 * cos((270 + 30 * st.wHour + st.wMinute / 2) * 3.141592 / 180)), int(hourLine.position1.y + 120 * sin((270 + 30 * st.wHour + st.wMinute / 2) * 3.141592 / 180)) };

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case 2:
			ball.transform.position += localPosition;

			if (ball.transform.position.x + ball.transform.scale.width >= background.transform.position.x + background.transform.scale.width - 1)
			{
				localPosition = RandLocalPosition(distance);
				localPosition.x *= (localPosition.x > 0) ? -1 : 1;
			}
			if (ball.transform.position.x <= background.transform.position.x + 1)
			{
				localPosition = RandLocalPosition(distance);
				localPosition.x *= (localPosition.x < 0) ? -1 : 1;
			}
			if (ball.transform.position.y + ball.transform.scale.height >= background.transform.position.y + background.transform.scale.height - 1)
			{
				localPosition = RandLocalPosition(distance);
				localPosition.y *= (localPosition.y > 0) ? -1 : 1;
			}
			if (ball.transform.position.y <= background.transform.position.y + 1)
			{
				localPosition = RandLocalPosition(distance);
				localPosition.y *= (localPosition.y < 0) ? -1 : 1;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		default:
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		DrawEllipse(hdc, ball.transform, ball.color);
		DrawRectangleEmpty(hdc, background.transform, background.color);
		DrawTextOut(hdc, timeText.transform, time, timeText.color);
		DrawEllipseEmpty(hdc, clockCircle.transform, clockCircle.color);
		DrawLine(hdc, secondLine.position1, secondLine.position2, secondLine.color);
		DrawLine(hdc, minuteLine.position1, minuteLine.position2, minuteLine.color);
		DrawLine(hdc, hourLine.position1, hourLine.position2, hourLine.color);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}