#pragma once
#include "MachineTile.h"
#include "OreTile.h"

class MinerTile : public MachineTile
{
private:
	float oreMultiplier;
	OreTile* currentOreTile;
	ItemContainer* itemCreator;

public:
	MinerTile();
	MinerTile(std::string tname, int tID, float om);
	MinerTile(const MinerTile& other);

	void init();

	Tile* copy() override;
	void update(float dt)override;
	bool giveItem(ItemContainer* it, int side)override;
	void connectToNearby() override;

	static const MinerTile baseMiner;
};

