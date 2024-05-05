#pragma once
#include "MachineTile.h"
#include "Item.h"
class ConveyorTile : public MachineTile
{
public:
	ConveyorTile() : MachineTile(), speed(0), itemSize(0), itemCList({}) {};
	ConveyorTile(std::string tname, int tID, float rot, bool cRot, float s, float is, bool mo) : MachineTile(tname, tID, rot, cRot,mo), speed(s), itemSize(is), itemCList({}) { };
	ConveyorTile(const ConveyorTile& other):
		MachineTile(other.tileName,other.tileID, other.rotation, other.canRotate,other.multiInput),
		speed(other.speed),
		itemSize(other.itemSize),
		itemCList({})
	{};



	Tile* copy() override;
	void connectToNearby() override;

	static float t;
	float speed;

	const float itemSize;

	std::vector<ItemContainer*> itemCList;

	static const ConveyorTile base;

	void update(float dt) override;
	std::vector<ItemRenderContainer> additiveDraw() override;
	bool giveItem(ItemContainer* it) override;
};

