#pragma once
#include "MachineTile.h"
class InventoryTile : public MachineTile
{
public: 
	InventoryTile();
	InventoryTile(std::string tname);
	InventoryTile(const InventoryTile& other);

	Tile* copy() override;
	bool giveItem(ItemContainer* it, int side)override;
	void connectToNearby() override;
	bool canConnect(int side, IOType io, MachineTile* mt) override;

	static const InventoryTile baseInventory;
};

