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
	Tileset(Texture& tex, int tsize, float tscale);

	Rectangle getRect(int id);

	int getTileSize() { return tileSize; }
	float getTileRatio() { return tileRatio; }

	Texture& getTileText() { return texture; }

private:
	Texture& texture;
	int tileSize = 16;

	float tileRatio;

	int maxTile;

	vector<Rectangle> tileList;
	
};

