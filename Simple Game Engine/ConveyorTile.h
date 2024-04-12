#pragma once
#include "MachineTile.h"
#include "Item.h"
class ConveyorTile : public MachineTile
{
	ConveyorTile() : MachineTile(), speed(0), itemSize(0), itemList({}) {};

	static float t;
	float speed;

	const float itemSize;

	std::vector<Item> itemList;
};

