#pragma once

#include "Stage.h"

class ElectricBox
{
private:
	int level;
	bool powerClicked;
	Stage* stage;

public:
	ElectricBox();

	void CreateStage();
	void MouseButtonDownEvent(LPARAM lParam);
	void MouseMoveEvent(LPARAM lParam);
	void MouseButtonUpEvent(LPARAM lParam);
	void ConveyElectric();
	void DeleteStage();
	void Draw(HDC hdc);

	~ElectricBox();
};