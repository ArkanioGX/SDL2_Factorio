#include "Tilemap.h"
#include "Camera.h"
#include "Actor.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Game.h"
#include <SDL.h>

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

void Tilemap::processInput(const InputState& inputState)
{
    getGridPosFromScreen(inputState.mouse.getPosition().x, inputState.mouse.getPosition().y);
}

Vector2 Tilemap::getGridPosFromScreen(float posx, float posy)
{
    Vector2 posInWorld = Camera::mainCam->getScreenPosInWorld(Vector2(posx,posy));
    return getGridPosFromWorld(posInWorld.x,posInWorld.y);
}

Vector2 Tilemap::getGridPosFromWorld(float posx, float posy)
{
    Vector2 tmPos = owner.getPosition();
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

