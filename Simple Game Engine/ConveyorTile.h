#pragma once
#include "MachineTile.h"
#include "Item.h"
class ConveyorTile : public MachineTile
{
public:
	ConveyorTile() : MachineTile(), speed(0), itemSize(0), itemList({}) {};
	ConveyorTile(int tID, float rot, bool cRot, float s, float is) : MachineTile(tID, rot, cRot), speed(s), itemSize(is), itemList({}) {};

	static float t;
	float speed;

	const float itemSize;

	std::vector<Item> itemList;

	static const ConveyorTile base;
};

