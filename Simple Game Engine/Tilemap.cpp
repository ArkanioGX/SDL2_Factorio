#include "Tilemap.h"

Tilemap::Tilemap(Tileset* tset): TilesetUsed(tset)
{
    TilemapContent = { {0,1,1,1},
                        {0,0,2,2},
                        {3,3,0,0}, 
                        {3,3,3,0} };
    maxTile = Vector2{ float(TilemapContent[0].size()),float(TilemapContent.size()) };
}

int Tilemap::getTileIdAtPos(float posx, float posy)
{
    return TilemapContent[posy][posx];
}

Vector2 Tilemap::getPosGridToLocal(float posx,float posy)
{
    float x = posx * TilesetUsed->getTileSize() * TilesetUsed->getTileRatio();
    float y = posy * TilesetUsed->getTileSize() * TilesetUsed->getTileRatio();
    return Vector2(x,y);
}
