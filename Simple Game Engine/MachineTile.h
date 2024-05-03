#pragma once
#include "Tile.h"
#include <vector>

class MachineTile : public Tile
{
public:

	MachineTile(): Tile(),inputTile({}), outputTile({}) {};

	MachineTile(std::string tname, int tID, float rot, bool cRot, bool mo) : Tile(tname,tID, rot, cRot, false, Type::Machine, PlaceableOn::Everything),multiInput(mo) {};

	MachineTile(const MachineTile& other) :
		Tile(other.tileName,other.tileID,other.rotation,other.canRotate,false, Type::Machine, PlaceableOn::Everything),
		inputTile(other.inputTile),
		outputTile(other.outputTile),
		multiInput(other.multiInput)
	{}

	~MachineTile();

	Tile* copy() override;

	Vector2 currentPos = Vector2::zero;

	bool multiInput = false;

	class MachineTileComponent* ownerComponent;

	std::vector<MachineTile*> inputTile, outputTile;
	virtual void update(float dt);
	virtual void additiveDraw();

	virtual void connectToNearby();

	void addInput(MachineTile* mt);
	void removeInput(MachineTile* mt);

	void addOutput(MachineTile* mt);
	void removeOutput(MachineTile* mt);
};

