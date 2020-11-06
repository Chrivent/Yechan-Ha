#include "Chess.h"

Chess::Chess()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
			pawn[j][i] = NULL;

		for (int i = 0; i < 2; i++)
		{
			knight[j][i] = NULL;
			bishop[j][i] = NULL;
			rook[j][i] = NULL;
		}

		queen[j] = NULL;
		king[j] = NULL;
	}

	turn = 0;
}

void Chess::CreatePiece()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (pawn[j][i] == NULL)
				pawn[j][i] = new Pawn;
		}

		for (int i = 0; i < 2; i++)
		{
			if (knight[j][i] == NULL)
				knight[j][i] = new Knight;

			if (bishop[j][i] == NULL)
				bishop[j][i] = new Bishop;

			if (rook[j][i] == NULL)
				rook[j][i] = new Rook;
		}

		if (queen[j] == NULL)
			queen[j] = new Queen;

		if (king[j] == NULL)
			king[j] = new King;
	}
}

void Chess::ArrangementTile()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
			tile[y][x].transform.position = { x * SCALE, y * SCALE };

		for (int x = (y + 1) % 2; x < 8; x += 2)
			tile[y][x].SetType(1);
	}
}

void Chess::ArrangementPiece()
{
	CreatePiece();

	for (int i = 0; i < 8; i++)
	{
		tile[6][i].AppendPiece(pawn[0][i]);
		tile[1][i].AppendPiece(pawn[1][i]);
		pawn[1][i]->SetType(1);
	}

	for (int i = 0; i < 2; i++)
	{
		tile[7][i * 5 + 1].AppendPiece(knight[0][i]);
		tile[0][i * 5 + 1].AppendPiece(knight[1][i]);
		knight[1][i]->SetType(1);

		tile[7][i * 3 + 2].AppendPiece(bishop[0][i]);
		tile[0][i * 3 + 2].AppendPiece(bishop[1][i]);
		bishop[1][i]->SetType(1);

		tile[7][i * 7].AppendPiece(rook[0][i]);
		tile[0][i * 7].AppendPiece(rook[1][i]);
		rook[1][i]->SetType(1);
	}

	tile[7][3].AppendPiece(queen[0]);
	tile[0][3].AppendPiece(queen[1]);
	queen[1]->SetType(1);

	tile[7][4].AppendPiece(king[0]);
	tile[0][4].AppendPiece(king[1]);
	king[1]->SetType(1);
}

Tile* Chess::GetTileByPosition(Position position)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (CheckPositionIsInTransform(tile[y][x].transform, position))
				return &tile[y][x];
		}
	}

	return NULL;
}

Piece* Chess::GetFriendlyPieceUnderMouse(LPARAM lParam)
{
	Position mousePosition = MousePosition(lParam);

	for (int i = 0; i < 8; i++)
	{
		if (pawn[turn][i] != NULL && CheckPositionIsInTransform(pawn[turn][i]->transform, mousePosition))
			return pawn[turn][i];
	}

	for (int i = 0; i < 2; i++)
	{
		if (knight[turn][i] != NULL && CheckPositionIsInTransform(knight[turn][i]->transform, mousePosition))
			return knight[turn][i];

		if (bishop[turn][i] != NULL && CheckPositionIsInTransform(bishop[turn][i]->transform, mousePosition))
			return bishop[turn][i];

		if (rook[turn][i] != NULL && CheckPositionIsInTransform(rook[turn][i]->transform, mousePosition))
			return rook[turn][i];
	}

	if (queen[turn] != NULL && CheckPositionIsInTransform(queen[turn]->transform, mousePosition))
		return queen[turn];

	if (king[turn] != NULL && CheckPositionIsInTransform(king[turn]->transform, mousePosition))
		return king[turn];

	return NULL;
}

void Chess::ShowPattern(Piece* piece)
{
	piece->SetPattern(tile);
}

void Chess::HidePattern()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (tile[y][x].GetMode() == MODE_ROUTE || tile[y][x].GetMode() == MODE_BASE)
				tile[y][x].SetMode(MODE_DEFAULT);
		}
	}
}

Piece* Chess::GetPieceSelected()
{
	for (int i = 0; i < 8; i++)
	{
		if (pawn[turn][i] != NULL && pawn[turn][i]->CheckSelected())
			return pawn[turn][i];
	}

	for (int i = 0; i < 2; i++)
	{
		if (knight[turn][i] != NULL && knight[turn][i]->CheckSelected())
			return knight[turn][i];

		if (bishop[turn][i] != NULL && bishop[turn][i]->CheckSelected())
			return bishop[turn][i];

		if (rook[turn][i] != NULL && rook[turn][i]->CheckSelected())
			return rook[turn][i];
	}

	if (queen[turn] != NULL && queen[turn]->CheckSelected())
		return queen[turn];

	if (king[turn] != NULL && king[turn]->CheckSelected())
		return king[turn];

	return NULL;
}

void Chess::DeleteOnePiece(Piece* piece)
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (pawn[j][i] != NULL && pawn[j][i] == piece)
			{
				delete pawn[j][i];
				pawn[j][i] = NULL;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (knight[j][i] != NULL && knight[j][i] == piece)
			{
				delete knight[j][i];
				knight[j][i] = NULL;
			}

			if (bishop[j][i] != NULL && bishop[j][i] == piece)
			{
				delete bishop[j][i];
				bishop[j][i] = NULL;
			}

			if (rook[j][i] != NULL && rook[j][i] == piece)
			{
				delete rook[j][i];
				rook[j][i] = NULL;
			}
		}

		if (queen[j] != NULL && queen[j] == piece)
		{
			delete queen[j];
			queen[j] = NULL;
		}

		if (king[j] != NULL && king[j] == piece)
		{
			delete king[j];
			king[j] = NULL;
		}
	}
}

void Chess::ChangeTurn()
{
	turn = (turn == 0) ? 1 : 0;
}

void Chess::Check()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (pawn[j][i] != NULL)
				pawn[j][i]->SetPattern(tile);
		}

		for (int i = 0; i < 2; i++)
		{
			if (knight[j][i] != NULL)
				knight[j][i]->SetPattern(tile);

			if (bishop[j][i] != NULL)
				bishop[j][i]->SetPattern(tile);

			if (rook[j][i] != NULL)
				rook[j][i]->SetPattern(tile);
		}

		if (queen[j] != NULL)
			queen[j]->SetPattern(tile);

		if (king[j] != NULL)
			king[j]->SetPattern(tile);

		Tile* kingTile = GetTileByPosition(king[(j == 0) ? 1 : 0]->transform.position);

		if (kingTile->GetMode() == MODE_ROUTE)
			kingTile->SetMode(MODE_CHECK);
		else
			kingTile->SetMode(MODE_DEFAULT);
	}
}

void Chess::Promotion(HWND hWnd)
{
	for (int i = 0; i < 8; i++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (pawn[turn][i] != NULL && tile[(turn == 0) ? 0 : 7][x].transform.position == pawn[turn][i]->transform.position && pawn[turn][i]->CheckPromotioned() == false)
			{
				delete pawn[turn][i];
				pawn[turn][i] = NULL;

				if (MessageBox(hWnd, TEXT("³ªÀÌÆ®·Î ½Â±ÞÇÏ½Ã°Ú½À´Ï±î?"), TEXT("½Â±Þ"), MB_YESNO) == IDYES)
					pawn[turn][i] = new Knight;
				else if (MessageBox(hWnd, TEXT("ºñ¼óÀ¸·Î ½Â±ÞÇÏ½Ã°Ú½À´Ï±î?"), TEXT("½Â±Þ"), MB_YESNO) == IDYES)
					pawn[turn][i] = new Bishop;
				else if (MessageBox(hWnd, TEXT("·èÀ¸·Î ½Â±ÞÇÏ½Ã°Ú½À´Ï±î?"), TEXT("½Â±Þ"), MB_YESNO) == IDYES)
					pawn[turn][i] = new Rook;
				else
				{
					pawn[turn][i] = new Queen;
					MessageBox(hWnd, TEXT("ÄýÀ¸·Î ½Â±ÞÇÏ¿´½À´Ï´Ù."), TEXT("½Â±Þ"), MB_OK);
				}

				pawn[turn][i]->SetType(turn);
				pawn[turn][i]->Promotioned();

				tile[(turn == 0) ? 0 : 7][x].RemovePiece();
				tile[(turn == 0) ? 0 : 7][x].AppendPiece(pawn[turn][i]);
			}
		}
	}
}

void Chess::Draw(HDC hdc)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
			tile[y][x].Draw(hdc);
	}

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (pawn[j][i] != NULL)
				pawn[j][i]->Draw(hdc);
		}

		for (int i = 0; i < 2; i++)
		{
			if (knight[j][i] != NULL)
				knight[j][i]->Draw(hdc);

			if (bishop[j][i] != NULL)
				bishop[j][i]->Draw(hdc);

			if (rook[j][i] != NULL)
				rook[j][i]->Draw(hdc);
		}

		if (queen[j] != NULL)
			queen[j]->Draw(hdc);

		if (king[j] != NULL)
			king[j]->Draw(hdc);
	}
}

void Chess::DeletePiece()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (pawn[j][i] != NULL)
			{
				delete pawn[j][i];
				pawn[j][i] = NULL;
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (knight[j][i] != NULL)
			{
				delete knight[j][i];
				knight[j][i] = NULL;
			}

			if (bishop[j][i] != NULL)
			{
				delete bishop[j][i];
				bishop[j][i] = NULL;
			}

			if (rook[j][i] != NULL)
			{
				delete rook[j][i];
				rook[j][i] = NULL;
			}
		}

		if (queen[j] != NULL)
		{
			delete queen[j];
			queen[j] = NULL;
		}

		if (king[j] != NULL)
		{
			delete king[j];
			king[j] = NULL;
		}
	}
}

Chess::~Chess()
{
	DeletePiece();
}