#include "Tilemap.h"
#include "Camera.h"
#include "Actor.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Game.h"
#include <SDL.h>
#include "OreTile.h"

bool Tilemap::isInsideMap(Vector2 pos)
{
    return (pos.x >= 0 && pos.x < maxTile.x && pos.y >= 0 && pos.y < maxTile.y);
}

Tilemap::Tilemap(Actor* ownerP, Tileset* tset, bool isEmpty = false):
    Component(ownerP),
    TilesetUsed(tset)
{
    if (!isEmpty) {
        std::vector<std::vector<int>> idMap{
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,4,4,3,3,3,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,4,4,4,4,3,3,3,1,1,1,1,1,1,1,1},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,4,4,4,3,3,3,3,3,3,1,1,1,1,1,1},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,3,3,3,0,0,3,3,3,3,1,1,1,1,1},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,3,0,0,2,0,0,3,3,3,1,1,1,1,1},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,4,4,3,0,2,2,0,3,3,3,3,1,1,1,1},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,4,4,3,0,0,3,3,3,4,3,3,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,4,3,3,3,4,4,4,3,3,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,4,4,3,3,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };
        setTileMapFromIdMap(idMap);
    }
    else {
        TilemapContent.resize(40, vector<Tile*>(40));
        for (int x = 0; x < TilemapContent.size(); x++) {
            for (int y = 0; y < TilemapContent[x].size(); y++) {
                TilemapContent[x][y] = nullptr;// Tile::Null;
            }
        }
    }
    /*
    TilemapContent = { {Tile::Ground,   Tile::Ground,   Tile::Ground,   Tile::Wall,     Tile::Wall},
                       {Tile::Ground,   Tile::Ground,   Tile::Ground,   Tile::Wall,     Tile::Wall},
                       {Tile::Ground,   Tile::Ground,   Tile::Water,    Tile::Water,    Tile::Wall},
                       {Tile::Ground,   Tile::Ore,      Tile::Water,    Tile::Water,    Tile::Water},
                       {Tile::Ground,   Tile::Ore,      Tile::Ore,      Tile::Water,    Tile::Water}
    };*/
    maxTile = Vector2{ float(TilemapContent[0].size()),float(TilemapContent.size()) };
}

void Tilemap::setTileMapFromIdMap(std::vector<std::vector<int>> &idMap) 
{
    TilemapContent.resize(idMap.size(), vector<Tile*>(idMap[0].size()));
    for (int x = 0; x < idMap.size(); x++) {
        for (int y = 0; y < idMap[x].size(); y++) {
            Tile TileToPlace = Tile::Null;
            switch (idMap[x][y]) {
            case 0:
                TileToPlace = Tile::DGround;
                break;
            case 1:
                TileToPlace = Tile::DWall;
                break;
            case 2:
                TileToPlace = OreTile::Ore;
                break;
            case 3:
                TileToPlace = Tile::DWater;
                break;
            case 4:
                TileToPlace = Tile::DDeepWater;
                break;
            default: break;
            }
            TileToPlace.setRandomTID();
            TilemapContent[x][y] = new Tile(TileToPlace);
        }
    }
}

Tile* Tilemap::getTileAtPos(float posx, float posy)
{
    return TilemapContent[posy][posx];
}

void Tilemap::setTileAtPos(float posx, float posy, Tile* t)
{
    t->setRandomTID();
    TilemapContent[posy][posx] = t;
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
    Vector2 origin = Vector2(getTexture().getWidth() / 2, getTexture().getHeight() / 2);
    Vector2 tmPos = owner.getPosition() - origin;
    Vector2 tmScale = owner.getScale();
    if(posx > tmPos.x &&
       posx < tmPos.x + (maxTile.x * TilesetUsed->getTileRatio().x * TilesetUsed->getTileSize() * tmScale.x) &&
        posy > tmPos.y &&
        posy < tmPos.y + (maxTile.y * TilesetUsed->getTileRatio().y * TilesetUsed->getTileSize() * tmScale.y))
    {
        int x = (posx - tmPos.x) / (TilesetUsed->getTileRatio().x * TilesetUsed->getTileSize() * tmScale.x);
        int y = (posy - tmPos.y) / (TilesetUsed->getTileRatio().y * TilesetUsed->getTileSize() * tmScale.y);
        //Log::info(" x : " + std::to_string(x) + " | y : " + std::to_string(y));
        return Vector2(x, y);
    }
    return Vector2::null;
}

void Tilemap::getLimit(Vector2& min, Vector2& max)
{
    min = owner.getPosition();
    max = min + (maxTile * TilesetUsed->getTileRatio() * TilesetUsed->getTileSize() * owner.getScale());
}

