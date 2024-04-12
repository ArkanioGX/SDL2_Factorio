#pragma once
#include "Tile.h"
#include <vector>

class MachineTile : public Tile
{
public:

	MachineTile() : Tile(),inputTile({}), outputTile({}) {};

	std::vector<MachineTile*> inputTile, outputTile;
	virtual void update(float dt);
	virtual void draw();

	void addInput(MachineTile* mt);
	void removeInput(MachineTile* mt);

	void addOutput(MachineTile* mt);
	void removeOutput(MachineTile* mt);
};

