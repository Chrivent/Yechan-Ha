#include "Chess.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Chess");

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	HDC hdc;
	PAINTSTRUCT ps;

	static Chess chess;
	static Piece* clickedPiece;
	static Piece* lastClickedPiece;
	static Piece* selectedPiece;
	static Piece* routePiece;
	static Tile* clickedTile;

	switch (iMessage)
	{
	case WM_CREATE:
		SetClientTransform(hWnd, { { 0, 0 }, { 8 * SCALE, 8 * SCALE } });

		chess.ArrangementTile();
		chess.ArrangementPiece();

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		clickedPiece = chess.GetFriendlyPieceUnderMouse(lParam);

		if (clickedPiece != NULL)
		{
			lastClickedPiece = chess.GetPieceSelected();

			if (lastClickedPiece != NULL)
			{
				lastClickedPiece->Unselect();
				chess.HidePattern();
			}

			clickedPiece->Select();
			chess.ShowPattern(clickedPiece);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else
		{
			clickedTile = chess.GetTileByPosition(MousePosition(lParam));
			selectedPiece = chess.GetPieceSelected();

			if (clickedTile->GetMode() == MODE_ROUTE)
			{
				chess.GetTileByPosition(selectedPiece->transform.position)->RemovePiece();

				routePiece = clickedTile->GetPiece();
				if (routePiece != NULL)
					chess.DeleteOnePiece(routePiece);

				clickedTile->AppendPiece(selectedPiece);
				selectedPiece->Moved();
				selectedPiece->Unselect();

				chess.Promotion(hWnd);

				chess.Check();
				chess.HidePattern();

				chess.ChangeTurn();

				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				if (selectedPiece != NULL)
				{
					selectedPiece->Unselect();

					chess.Check();
					chess.HidePattern();

					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		chess.Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}