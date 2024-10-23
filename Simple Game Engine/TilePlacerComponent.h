#pragma once
#include "Component.h"
#include "Tile.h"
#include <vector>
#include <map>
#include <SDL_scancode.h>

struct PreviewTile {
	Tile* tile;
	Vector2 pos;

	bool operator== (const PreviewTile& t) {
		return (t.pos.x == pos.x && t.pos.y == pos.y);
	}
};

class TilePlacerComponent : public Component
{
public:
	TilePlacerComponent(class Actor* ownerP, class Tilemap* tmap, std::vector<Tile*> tList);

	void processInput(const struct InputState& inputState) override;

	void setNewTileToPlace(const InputState& inputState);

	void confirmBuild();

	void placePreviewTile(Vector2 pos);

	void placeTile(Vector2 pos, Tile* t);

	bool canPlace(Vector2 pos);

	void removeTile(Vector2 pos);

	std::vector<PreviewTile> getPrevewTiles();

private:

	std::vector<Tile*> tileList;

	std::vector<PreviewTile> pTileList;

	int currentRotation = 0;

	int currentTilePlacedOrder = 0;

	class Tilemap* map;
	
	Tile* tileToPlace;
	Vector2 lastTilePos = Vector2(-1,-1);

	std::map<SDL_Scancode, int> inputMap{
		{SDL_SCANCODE_0,9},
		{ SDL_SCANCODE_1,0 },
		{ SDL_SCANCODE_2,1 },
		{ SDL_SCANCODE_3,2 },
		{ SDL_SCANCODE_4,3 },
		{ SDL_SCANCODE_5,4 },
		{ SDL_SCANCODE_6,5 },
		{ SDL_SCANCODE_7,6 },
		{ SDL_SCANCODE_8,7 },
		{ SDL_SCANCODE_9,8 },
	};
};

