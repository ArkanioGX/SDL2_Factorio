#pragma once
#include "MachineTile.h"
#include "Item.h"
class ConveyorTile : public MachineTile
{
public:
	ConveyorTile() : MachineTile(), speed(0), itemSize(0), itemCList({}) { init(); };
	ConveyorTile(std::string tname, int tID, float rot, bool cRot, float s, float is, bool mo) : MachineTile(tname, tID, rot, cRot), speed(s), itemSize(is), itemCList({}) { init(); };
	ConveyorTile(const ConveyorTile& other):
		MachineTile(other.tileName,other.tileID, other.rotation, other.canRotate),
		speed(other.speed),
		itemSize(other.itemSize),
		itemCList({})
	{
		init();
	};

	~ConveyorTile();

	void init();

	Tile* copy() override;
	void connectToNearby() override;
	bool canConnect(int side, IOType io, MachineTile* mt) override;

	static float t;
	float speed;

	const int itemSize;

	std::vector<ItemContainer*> itemCList;

	static const ConveyorTile base;
	static const ConveyorTile upgrade;

	void update(float dt) override;
	std::vector<ItemRenderContainer> additiveDraw() override;
	bool giveItem(ItemContainer* it, int side) override;

	bool nextItemContainer(int contId);
};

