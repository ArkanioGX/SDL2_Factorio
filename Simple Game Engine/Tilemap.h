#pragma once
#include "Tileset.h"
#include <vector>
#include <string>
#include "Vector2.h"

class Tilemap
{
private:
	Tileset* TilesetUsed;

	vector<vector<int>> TilemapContent;

	Vector2 maxTile;
public:
	Tilemap(Tileset* tset);

	int getTileIdAtPos(float posx, float posy);

	Vector2 getPosGridToLocal(float posx,float posy);

	Vector2 getMaxTile() { return maxTile; }

	Rectangle getRectFromID(int id) { return TilesetUsed->getRect(id); }

	Texture& getTexture() { return TilesetUsed->getTileText(); }

	Vector2 getGridPosFromWorld(float posx, float posy, Actor* tmapActor);

	Tileset* getTileset() { return TilesetUsed; };
};

