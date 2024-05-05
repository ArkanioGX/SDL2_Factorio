#pragma once
#include "Tile.h"
#include "Item.h"
class OreTile : public Tile
{
public:

	OreTile() :Tile(), drop(Item::Test) {};
	OreTile(std::string tname,float tID, Item i,float d, float rot, bool cRot,bool rRot, PlaceableOn pOn) : Tile(tname,tID, rot, cRot,rRot, Type::Ore, pOn),drop(i),density(d) {};

	Item drop;
	float density;

	static const OreTile Ore;
};

