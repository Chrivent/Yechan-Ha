#include "Pawn.h"

void Pawn::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (type == 0) ? TEXT("block_w_00.bmp") : TEXT("block_b_00.bmp"));
}

void Pawn::SetPattern(Tile tile[8][8])
{
	int baseY, baseX;
	GetBaseTileIndex(tile, baseY, baseX);

	tile[baseY][baseX].SetMode(MODE_BASE);

	if (moved)
	{
		Tile* target = &tile[baseY + ((type == 0) ? -1 : 1)][baseX];

		if (target->GetPiece() == NULL)
			target->SetMode(MODE_ROUTE);
	}
	else
	{
		for (int i = 1; i <= 2; i++)
		{
			Tile* target = &tile[baseY + ((type == 0) ? -i : i)][baseX];

			if (target->GetPiece() == NULL)
				target->SetMode(MODE_ROUTE);
			else
				break;
		}
	}

	if (baseX - 1 >= 0)
	{
		Tile* target = &tile[baseY + ((type == 0) ? -1 : 1)][baseX - 1];

		if (target->GetPiece() != NULL && target->GetPiece()->GetType() != type)
			target->SetMode(MODE_ROUTE);
	}

	if (baseX + 1 < 8)
	{
		Tile* target = &tile[baseY + ((type == 0) ? -1 : 1)][baseX + 1];

		if (target->GetPiece() != NULL && target->GetPiece()->GetType() != type)
			target->SetMode(MODE_ROUTE);
	}
}