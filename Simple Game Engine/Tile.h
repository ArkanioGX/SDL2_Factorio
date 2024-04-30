#pragma once

//class OreTile;
#include<vector>
#include "Random.h"
#include <Time.h>
#include "Maths.h"
#include "Log.h"
#include <string>

class TilemapSpriteComponent;

class Tile
{
public:
	enum PlaceableOn { Everything, Nothing, OnlyTransport };
	enum Type { Basic, Ore, Machine };

	

	static unsigned int seed;

	Tile() : tileID(0), randomTileID(false),randomRotate(false), rotation(0), canRotate(true), type(Type::Basic), placeType(PlaceableOn::Nothing) {};
	Tile(std::string tname, int tID, float rot, bool cRot,bool rRot, Type t, PlaceableOn pOn) : tileName(tname), tileID(tID),  randomTileID(false), rotation(rot), canRotate(cRot),randomRotate(rRot), type(t), placeType(pOn) {}
	Tile(std::string tname, std::vector<int> tID,  float rot, bool cRot, bool rRot,Type t, PlaceableOn pOn) :tileName(tname), tileIDlist(tID),tileID(tID[0]), randomTileID(true), rotation(rot), canRotate(cRot), randomRotate(rRot), type(t), placeType(pOn) {
	}

	Tile(const Tile& other) : 
		tileID(other.tileID),
		tileIDlist(other.tileIDlist),
		randomTileID(other.randomTileID),
		rotation(other.rotation),
		canRotate(other.canRotate),
		randomRotate(other.randomRotate),
		type(other.type),
		placeType(other.placeType)
	{} 

	virtual Tile* copy();

	//Tileset* tset;
	bool canRotate;
	bool randomRotate;
	float rotation;
	int tileID;
	std::vector<int> tileIDlist;
	Type type;
	PlaceableOn placeType;
	bool randomTileID;
	std::string tileName;
	std::string name;

	static const Tile Null;

	//Desert Tile
	static const Tile DGround;
	static const Tile DWall;
	static const Tile DWater;
	static const Tile DDeepWater;

	void setRandomTID();

	inline bool operator!=(const Tile* rt) {
		return tileName.compare(rt->tileName) != 0;
	}

	
	inline bool operator==(const Tile* rt) {
		return tileName.compare(rt->tileName) == 0;
	}
};
