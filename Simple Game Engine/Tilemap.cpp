#include "Tilemap.h"
#include "Camera.h"
#include "Actor.h"

Tilemap::Tilemap(Actor* ownerP, Tileset* tset):
    Component(ownerP),
    TilesetUsed(tset)
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

Vector2 Tilemap::getGridPosFromScreen(float posx, float posy)
{
    Vector2 posInWorld = Camera::mainCam->getScreenPosInWorld(Vector2(posx,posy));
    return getGridPosFromWorld(posInWorld.x,posInWorld.y);
}

Vector2 Tilemap::getGridPosFromWorld(float posx, float posy)
{

    if(posx > owner.getPosition().x &&
       posx < owner.getPosition().x + (maxTile.x * TilesetUsed->getTileRatio().x * TilesetUsed->getTileSize() * owner.getScale().x))
    {
        Log::info("IN !!");
    }
    Vector2 tmPos = owner.getPosition();
    Vector2 tmScale = owner.getScale();

    

    return Vector2();
}

