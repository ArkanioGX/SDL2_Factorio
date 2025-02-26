#pragma once
#include "Tileset.h"
#include <vector>
#include <string>
#include "Vector2.h"
#include "Component.h"
#include "Tile.h"

struct Chunk {

};

class Tilemap : public Component
{
private:
	Tileset* TilesetUsed;

	vector<vector<Tile*>> TilemapContent;

	Vector2 maxTile;
	int ChunkSize = 8;

	void setTileMapFromIdMap(std::vector<std::vector<int>> &idMap);


public:
	bool isInsideMap(Vector2 pos);

	Tilemap(Actor* ownerP, Tileset* tset, bool isEmpty);

	Tile* getTileAtPos(float posx, float posy);


	void setTileAtPos(float posx, float posy, Tile* t);
	void removeTileAtPos(float posx, float posy);

	Vector2 getPosGridToLocal(float posx,float posy);

	Vector2 getMaxTile() { return maxTile; }
	Vector2 getMaxChunks() { return Vector2(ceil(maxTile.x/ChunkSize), ceil(maxTile.y / ChunkSize )); }

	Rectangle getRectFromID(int id) { return TilesetUsed->getRect(id); }

	Texture& getTexture() { return TilesetUsed->getTileText(); }

	

	Tileset* getTileset() { return TilesetUsed; };

	Vector2 getGridPosFromScreen(float posx, float posy);
	Vector2 getGridPosFromWorld(float posx, float posy);

	void getLimit(Vector2& min, Vector2& max);
};

