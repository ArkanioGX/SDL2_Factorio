#pragma once
#include "Tile.h"
#include <vector>

class MachineTile : public Tile
{
public:

	MachineTile() : Tile(),inputTile({}), outputTile({}) {};
	//Tile(int tID, float rot, bool cRot, bool rRot, Type t, PlaceableOn pOn);
	MachineTile(int tID, float rot, bool cRot) : Tile(tID, rot, cRot, false, Type::Machine, PlaceableOn::Everything) {};

	std::vector<MachineTile*> inputTile, outputTile;
	virtual void update(float dt, class MachineTileComponent* msc = nullptr);
	virtual void additiveDraw();

	void addInput(MachineTile* mt);
	void removeInput(MachineTile* mt);

	void addOutput(MachineTile* mt);
	void removeOutput(MachineTile* mt);
};

