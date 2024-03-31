#pragma once
#include "Component.h"
#include "Tile.h"
class TilePlacerComponent : public Component
{
public:
	TilePlacerComponent(class Actor* ownerP, class Tilemap* tmap);

	void processInput(const struct InputState& inputState) override;

private:

	class Tilemap* map;
	
	Tile tileToPlace;
};

