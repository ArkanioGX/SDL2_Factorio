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

struct IOTile
{
	MachineTile* mTile;
	int side;
};

enum IOType {
	Output,
	Input
}
;

struct ItemRenderContainer {
public:
	Vector2 pos;
	Texture tex;
};

class MachineTile : public Tile
{
public:

	MachineTile(): Tile(),inputTile({}), outputTile({}) {};

	MachineTile(std::string tname, int tID, float rot, bool cRot) : Tile(tname,tID, rot, cRot, false, Type::Machine, PlaceableOn::Everything) {};

	MachineTile(const MachineTile& other) :
		Tile(other.tileName,other.tileID,other.rotation,other.canRotate,false, Type::Machine, PlaceableOn::Everything),
		inputTile(other.inputTile),
		outputTile(other.outputTile)
	{}

	~MachineTile();

	Tile* copy() override;

	Vector2 currentPos = Vector2::zero;

	class MachineTileComponent* ownerComponent;

	std::vector<MachineTile*> inputTile, outputTile;
	virtual void update(float dt);
	virtual std::vector<ItemRenderContainer> additiveDraw();

	virtual bool giveItem(ItemContainer* it, int side);

	virtual void connectToNearby();
	virtual bool canConnect(int side, IOType io, MachineTile* mt);

	void addInput(MachineTile* mt);
	void removeInput(MachineTile* mt);

	void addOutput(MachineTile* mt);
	void removeOutput(MachineTile* mt);

	Vector2 getPosFromSide(int s) {
		switch (s) {
		case 0:
			return Vector2(-1, 0);
		case 1:
			return Vector2(0, 1);
		case 2:
			return Vector2(1, 0);
		case 3:
			return Vector2(0, -1);
		}
		return Vector2(0, 0);
	}
};



