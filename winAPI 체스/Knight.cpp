#include "Knight.h"

void Knight::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (type == 0) ? TEXT("block_w_01.bmp") : TEXT("block_b_01.bmp"));
}

void Knight::SetPattern(Tile tile[8][8])
{
	int baseY, baseX;
	GetBaseTileIndex(tile, baseY, baseX);

	tile[baseY][baseX].SetMode(MODE_BASE);

	if (baseY - 2 >= 0)
	{
		if (baseX - 1 >= 0)
		{
			Tile* target = &tile[baseY - 2][baseX - 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		if (baseX + 1 < 8)
		{
			Tile* target = &tile[baseY - 2][baseX + 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}
	}

	if (baseY - 1 >= 0)
	{
		if (baseX - 2 >= 0)
		{
			Tile* target = &tile[baseY - 1][baseX - 2];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		if (baseX + 2 < 8)
		{
			Tile* target = &tile[baseY - 1][baseX + 2];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}
	}

	if (baseY + 1 < 8)
	{
		if (baseX - 2 >= 0)
		{
			Tile* target = &tile[baseY + 1][baseX - 2];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		if (baseX + 2 < 8)
		{
			Tile* target = &tile[baseY + 1][baseX + 2];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}
	}

	if (baseY + 2 < 8)
	{
		if (baseX - 1 >= 0)
		{
			Tile* target = &tile[baseY + 2][baseX - 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		if (baseX + 1 < 8)
		{
			Tile* target = &tile[baseY + 2][baseX + 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}
	}
}