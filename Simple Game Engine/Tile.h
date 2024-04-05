#pragma once

//class OreTile;
#include<vector>
#include "Random.h"
#include <Time.h>
#include "Maths.h"

class Tile
{
public:
	enum PlaceableOn { Everything, Nothing, OnlyTransport };
	enum Type { Basic, Ore, Machine };

	static unsigned int seed;

	Tile() : tileID(-1), randomTileID(false), rotation(0), canRotate(true), type(Type::Basic), placeType(PlaceableOn::Nothing) {};
	Tile(int tID, float rot, bool cRot,bool rRot, Type t, PlaceableOn pOn) : tileID(tID),  randomTileID(false), rotation(rot), canRotate(cRot),randomRotate(rRot), type(t), placeType(pOn) {}
	Tile(std::vector<int> tID,  float rot, bool cRot, bool rRot,Type t, PlaceableOn pOn) : tileIDlist(tID),tileID(tID[0]), randomTileID(true), rotation(rot), canRotate(cRot), randomRotate(rRot), type(t), placeType(pOn) {
	}

	//Tileset* tset;
	bool canRotate;
	bool randomRotate;
	float rotation;
	int tileID;
	std::vector<int> tileIDlist;
	Type type;
	PlaceableOn placeType;
	bool randomTileID;

	static const Tile Null;

	//Desert Tile
	static const Tile DGround;
	static const Tile DWall;
	static const Tile DWater;
	static const Tile DDeepWater;

	void setRandomTID();
};
