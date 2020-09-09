#pragma once
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

const int board_start_width = 125;
const int board_start_height = 125;
const int board_width = 125 * 9;
const int board_height = 125 * 9;

const int max = 8;

enum PIECE 
{
	PIECE_KING,
	PIECE_QUEEN,
	PIECE_KNIGHT,
	PIECE_ROOK,
	PIECE_BISHOP,
	PIECE_PAWN
};

enum PLAYER
{
	PLAYER_BLACK,
	PLAYER_WHITE
};