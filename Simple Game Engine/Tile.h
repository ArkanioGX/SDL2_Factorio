#pragma once

//class OreTile;

class Tile
{
public:
	enum PlaceableOn { Everything, Nothing, OnlyTransport };
	enum Type { Basic, Ore, Machine };

	Tile() : tileID(-1),rotation(0), canRotate(true),type(Type::Basic),placeType(PlaceableOn::Nothing){};
	Tile(float tID,  float rot, bool cRot,Type t, PlaceableOn pOn) : tileID(tID), rotation(rot), canRotate(cRot), type(t), placeType(pOn) {}

	//Tileset* tset;
	bool canRotate;
	float rotation;
	int tileID;
	Type type;
	PlaceableOn placeType;

	static const Tile Null;

	static const Tile Ground;
	static const Tile Wall;
	static const Tile Water;
};
