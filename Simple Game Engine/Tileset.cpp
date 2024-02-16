#include "Tileset.h"

Tileset::Tileset(Texture& tex, int tsize = 16, float tscale = 0.5):
	tileSize(tsize),
	texture(tex)
{
	int tileNumberW = texture.getWidth() / tsize;
	int tileNumberH = texture.getHeight() / tsize;
	for (int y = 0; y < tileNumberH; y++) {
		for (int x = 0; x < tileNumberW; x++) {
			Rectangle r = { x, y, x + tsize, y + tsize };
			tileList.push_back(r);
		}
	}

	tileRatio = tsize / texture.getWidth();
}

Rectangle Tileset::getRect(int id)
{
	return tileList[id];
}
