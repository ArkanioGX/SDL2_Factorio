#pragma once
#include "Tile.h"
#include <vector>
#include "Item.h"

struct ItemContainer {
	Item item;
	float baseT = 0;
	float t = 0;
	int iSize = 1;
	bool hasItem() {
		return !item.isNull();
	}
	bool isBlocked = false;
	int inSide = 0;

};

struct ItemRenderContainer {
public:
	Vector2 pos;
	Texture tex;
};

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
	virtual std::vector<ItemRenderContainer> additiveDraw();

	virtual bool giveItem(ItemContainer* it, int side);

	virtual void connectToNearby();

	void addInput(MachineTile* mt);
	void removeInput(MachineTile* mt);

	void addOutput(MachineTile* mt);
	void removeOutput(MachineTile* mt);
};

