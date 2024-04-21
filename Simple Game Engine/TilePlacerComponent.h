#pragma once
#include "Component.h"
#include "Tile.h"
#include <vector>
#include <map>
#include <SDL_scancode.h>
class TilePlacerComponent : public Component
{
public:
	TilePlacerComponent(class Actor* ownerP, class Tilemap* tmap, std::vector<Tile*> tList);

	void processInput(const struct InputState& inputState) override;

	void setNewTileToPlace(const InputState& inputState);

	void placeTile(Vector2 pos);

	bool canPlace(Vector2 pos);

private:

	std::vector<Tile*> tileList;

	int currentRotation = 0;

	class Tilemap* map;
	
	Tile* tileToPlace;

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

