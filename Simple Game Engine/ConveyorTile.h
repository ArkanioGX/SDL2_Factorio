#pragma once
#include "MachineTile.h"
#include "Item.h"
class ConveyorTile : public MachineTile
{
public:
	ConveyorTile() : MachineTile(), speed(0), itemSize(0), itemList({}) {};
	ConveyorTile(std::string tname, int tID, float rot, bool cRot, float s, float is) : MachineTile(tname, tID, rot, cRot), speed(s), itemSize(is), itemList({}) {};
	ConveyorTile(const ConveyorTile& other):
		MachineTile(other.tileName,other.tileID, other.rotation, other.canRotate),
		speed(other.speed),
		itemSize(other.itemSize),
		itemList({})
	{};

	Tile* copy() override;

	static float t;
	float speed;

	const float itemSize;

	std::vector<Item> itemList;

	static const ConveyorTile base;

	void update(float dt) override;
};

