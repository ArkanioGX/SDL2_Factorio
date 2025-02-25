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

	int lastOutput = 0;
	IOTile getCurrentOutput();

	void init();

	Tile* copy() override;
	void update(float dt)override;
	bool giveItem(ItemContainer* it, int side)override;
	void connectToNearby() override;
	bool canConnect(int side, IOType io, MachineTile* mt) override;

	static const MinerTile baseSMiner;
	static const MinerTile baseIMiner;
};

