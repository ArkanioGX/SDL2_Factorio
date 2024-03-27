#include "Tileset.h"

Tileset::Tileset(Texture& tex, int tsize = 16):
	tileSize(tsize),
	texture(tex)
{
	int tileNumberW = texture.getWidth() / tsize;
	int tileNumberH = texture.getHeight() / tsize;
	for (int y = 0; y < tileNumberH; y++) {
		for (int x = 0; x < tileNumberW; x++) {
			int xcorner = x * tsize;
			int ycorner = y * tsize;
			Rectangle r = { xcorner, ycorner, tsize, tsize };
			tileList.push_back(r);
		}
	}

	tileRatio = Vector2(tileNumberW, tileNumberH);
}

Rectangle Tileset::getRect(int id)
{
	return tileList[id];
}
