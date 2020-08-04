#pragma once

class Inventory
{
protected:
	Inventory* parent;
	Inventory* child;

public:
	Inventory()
	{
		parent = NULL;
		child = NULL;
	}
	void SetParent(Inventory* parent)
	{
		this->parent = parent;
	}
	void SetChild(Inventory* child)
	{
		this->child = child;
	}
	Inventory* GetParent()
	{
		return parent;
	}
	Inventory* GetChild()
	{
		return child;
	}

	void AddInventory(Inventory* inventory)
	{
		inventory->SetParent(this);
		this->SetChild(inventory);
	}
};