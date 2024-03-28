#pragma once
#include <string>
#include "Rectangle.h"
#include <vector>
#include "Assets.h"
#include "Log.h"

using namespace std;

class Tileset
{
public:
	Tileset(Texture& tex, int tsize);

	Rectangle getRect(int id);

	int getTileSize() { return tileSize; }
	Vector2 getTileRatio() { return tileRatio; }

	Texture& getTileText() { return texture; }

private:
	Texture& texture;
	int tileSize = 16;

	Vector2 tileRatio;

	int maxTile;
	 
	vector<Rectangle> tileList;
	
};

