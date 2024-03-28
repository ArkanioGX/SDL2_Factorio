#pragma once
struct Tile
{
	enum PlaceableOn { Everything, Nothing, OnlyTransport };

	Tile() : tileID(-1),rotation(0),placeType(PlaceableOn::Nothing){};
	Tile(float tID,  float rot, PlaceableOn pOn) : tileID(tID), rotation(rot), placeType(PlaceableOn::Nothing) {}

	//Tileset* tset;
	float rotation;
	int tileID;
	PlaceableOn placeType;

	static const Tile Null;

	static const Tile Ground;
	static const Tile Wall;
	static const Tile Ore; //Will be moved to adequate struct
	static const Tile Water;
};
