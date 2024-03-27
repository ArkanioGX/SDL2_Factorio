#include "Tilemap.h"
#include "Camera.h"

Tilemap::Tilemap(Tileset* tset): TilesetUsed(tset)
{
    TilemapContent = { {0,1,2},
                       {1,2,3},
                       {2,3,4}
    };
    maxTile = Vector2{ float(TilemapContent[0].size()),float(TilemapContent.size()) };
}

int Tilemap::getTileIdAtPos(float posx, float posy)
{
    return TilemapContent[posy][posx];
}

Vector2 Tilemap::getPosGridToLocal(float posx,float posy)
{
    float x = posx * TilesetUsed->getTileSize() * TilesetUsed->getTileRatio().x;
    float y = posy * TilesetUsed->getTileSize() * TilesetUsed->getTileRatio().y;
    return Vector2(x,y);
}

Vector2 Tilemap::getGridPosFromWorld(float posx, float posy, Actor* tmapActor)
{
    float currZoom = Camera::mainCam->getZoom() ;
    Vector2 camPos = Camera::mainCam->getPos();
    Vector2 tmPos = tmapActor->getPosition();
    Vector2 tmScale = tmapActor->getScale();



    return Vector2();
}

