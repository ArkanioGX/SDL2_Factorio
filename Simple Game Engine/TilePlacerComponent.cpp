#include "TilePlacerComponent.h"
#include "Actor.h"
#include "Tilemap.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Game.h"
#include <SDL.h>
#include "Maths.h"

TilePlacerComponent::TilePlacerComponent(Actor* ownerP, Tilemap* tmap, std::vector<Tile> tList):
	Component(ownerP),
	map(tmap),
	tileToPlace(tList[0]),
	tileList(tList)
{}


void TilePlacerComponent::processInput(const InputState& inputState)
{
	Vector2 gPos = map->getGridPosFromScreen(inputState.mouse.getPosition().x, inputState.mouse.getPosition().y);
	if (gPos != Vector2::null && inputState.mouse.getButtonState(1) == ButtonState::Held){
		if (map->getTileIdAtPos(gPos.x, gPos.y).placeType == Tile::PlaceableOn::Everything) {
			Tile t = tileToPlace;
			if (t.canRotate) {
				t.rotation = currentRotation;
			}
			map->setTileAtPos(gPos.x, gPos.y, t);
		}
	}

	if (inputState.keyboard.getKeyState(SDL_SCANCODE_Q) == ButtonState::Pressed) {
		currentRotation = (currentRotation + Maths::piOver2) ;
	}
	if (inputState.keyboard.getKeyState(SDL_SCANCODE_E) == ButtonState::Pressed) {
		currentRotation = (currentRotation - Maths::piOver2);
	}
	setNewTileToPlace(inputState);
}

void TilePlacerComponent::setNewTileToPlace(const InputState& inputState)
{
	for (const auto& input : inputMap) {
		if (inputState.keyboard.getKeyState(input.first) == ButtonState::Pressed) {
			int id = input.second;
			if (id < tileList.size()) {
				tileToPlace = tileList[id];
			}
		}
	}
}
