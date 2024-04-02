#include "TilePlacerComponent.h"
#include "Actor.h"
#include "Tilemap.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Game.h"
#include <SDL.h>

TilePlacerComponent::TilePlacerComponent(Actor* ownerP, Tilemap* tmap):
	Component(ownerP),
	map(tmap),
	tileToPlace(Tile::Ore)
{}

void TilePlacerComponent::processInput(const InputState& inputState)
{
	Vector2 gPos = map->getGridPosFromScreen(inputState.mouse.getPosition().x, inputState.mouse.getPosition().y);
	if (gPos != Vector2::null && inputState.mouse.getButtonState(1) == ButtonState::Pressed){
		if (map->getTileIdAtPos(gPos.x, gPos.y).placeType == Tile::PlaceableOn::Everything) {
			map->setTileAtPos(gPos.x, gPos.y, tileToPlace);
		}
	}
}
