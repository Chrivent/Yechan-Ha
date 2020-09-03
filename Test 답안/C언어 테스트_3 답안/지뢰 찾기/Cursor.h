#pragma once

#include "Object.h"

class Cursor : public Object
{
public:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void DrawCursor();
};