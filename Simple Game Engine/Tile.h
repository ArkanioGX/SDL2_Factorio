#pragma once
struct Tile
{
	Tile() : tileID(-1),rotation(0){};
	Tile(float tID,  float rot) : tileID(tID), rotation(rot) {}

	//Tileset* tset;
	float rotation;
	int tileID;

	static const Tile Null;

	static const Tile Ground;
	static const Tile Wall;
	static const Tile Ore; //Will be moved to adequate struct
	static const Tile Water;
};
