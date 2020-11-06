#include "King.h"

void King::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (type == 0) ? TEXT("block_w_05.bmp") : TEXT("block_b_05.bmp"));
}

void King::SetPattern(Tile tile[8][8])
{
	int baseY, baseX;
	GetBaseTileIndex(tile, baseY, baseX);

	if (tile[baseY][baseX].GetMode() != MODE_CHECK)
		tile[baseY][baseX].SetMode(MODE_BASE);

	if (baseY - 1 >= 0)
	{
		if (baseX - 1 >= 0)
		{
			Tile* target = &tile[baseY - 1][baseX - 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		if (baseX + 1 < 8)
		{
			Tile* target = &tile[baseY - 1][baseX + 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		Tile* target = &tile[baseY - 1][baseX];

		if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
			target->SetMode(MODE_ROUTE);
	}

	if (baseY + 1 < 8)
	{
		if (baseX - 1 >= 0)
		{
			Tile* target = &tile[baseY + 1][baseX - 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		if (baseX + 1 < 8)
		{
			Tile* target = &tile[baseY + 1][baseX + 1];

			if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);
		}

		Tile* target = &tile[baseY + 1][baseX];

		if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
			target->SetMode(MODE_ROUTE);
	}

	if (baseX - 1 >= 0)
	{
		Tile* target = &tile[baseY][baseX - 1];

		if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
			target->SetMode(MODE_ROUTE);
	}

	if (baseX + 1 < 8)
	{
		Tile* target = &tile[baseY][baseX + 1];

		if (target->GetPiece() == NULL || target->GetPiece()->GetType() != type)
			target->SetMode(MODE_ROUTE);
	}
}