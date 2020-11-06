#include "Bishop.h"

void Bishop::Draw(HDC hdc)
{
	DrawBitmapTransparent(hdc, transform, (type == 0) ? TEXT("block_w_02.bmp") : TEXT("block_b_02.bmp"));
}

void Bishop::SetPattern(Tile tile[8][8])
{
	int baseY, baseX;
	GetBaseTileIndex(tile, baseY, baseX);

	tile[baseY][baseX].SetMode(MODE_BASE);

	int i = 1;
	while (baseY - i >= 0 && baseX - i >= 0)
	{
		Tile* target = &tile[baseY - i][baseX - i];

		if (target->GetPiece() == NULL)
			target->SetMode(MODE_ROUTE);
		else
		{
			if (target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);

			break;
		}

		i++;
	}

	i = 1;
	while (baseY - i >= 0 && baseX + i < 8)
	{
		Tile* target = &tile[baseY - i][baseX + i];

		if (target->GetPiece() == NULL)
			target->SetMode(MODE_ROUTE);
		else
		{
			if (target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);

			break;
		}

		i++;
	}

	i = 1;
	while (baseY + i < 8 && baseX - i >= 0)
	{
		Tile* target = &tile[baseY + i][baseX - i];

		if (target->GetPiece() == NULL)
			target->SetMode(MODE_ROUTE);
		else
		{
			if (target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);

			break;
		}

		i++;
	}

	i = 1;
	while (baseY + i < 8 && baseX + i < 8)
	{
		Tile* target = &tile[baseY + i][baseX + i];

		if (target->GetPiece() == NULL)
			target->SetMode(MODE_ROUTE);
		else
		{
			if (target->GetPiece()->GetType() != type)
				target->SetMode(MODE_ROUTE);

			break;
		}

		i++;
	}
}