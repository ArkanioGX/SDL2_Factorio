#include "TilePlacerComponent.h"
#include "Actor.h"
#include "Tilemap.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Game.h"
#include <SDL.h>
#include "Maths.h"
#include "MachineTileComponent.h"
#include "Tile.h"
#include "MachineTile.h"

TilePlacerComponent::TilePlacerComponent(Actor* ownerP, Tilemap* tmap, std::vector<Tile*> tList):
	Component(ownerP),
	map(tmap),
	tileToPlace(tList[0]),
	tileList(tList)
{}


void TilePlacerComponent::processInput(const InputState& inputState)
{
	Vector2 gPos = map->getGridPosFromScreen(inputState.mouse.getPosition().x, inputState.mouse.getPosition().y);
	if (gPos != Vector2::null && inputState.mouse.getButtonState(1) == ButtonState::Held){
		if (canPlace(gPos)) {
			placeTile(gPos);
		}
	}

	if (inputState.keyboard.getKeyState(SDL_SCANCODE_Q) == ButtonState::Pressed) {
		currentRotation = ( currentRotation + 1) % 4 ;
	}
	if (inputState.keyboard.getKeyState(SDL_SCANCODE_E) == ButtonState::Pressed) {
		currentRotation = ( currentRotation - 1) % 4;
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

void TilePlacerComponent::placeTile(Vector2 pos)
{
	Tile* t = new Tile(*tileToPlace);
	if (t->canRotate) {
		t->rotation = currentRotation * Maths::piOver2;
	}
	if (t->type == Tile::Type::Machine) {
		MachineTileComponent* mtc = owner.getComponent<MachineTileComponent*>();
		if (mtc != nullptr) {
			mtc->addMTile(static_cast<MachineTile*>(t));
		}
		Tile* tileAtPlace = map->getTileAtPos(pos.x, pos.y);
		if (tileAtPlace != nullptr) {
			if (tileAtPlace->type == Tile::Type::Machine) {
				mtc->removeMTile(static_cast<MachineTile*>(t));
			}
		}

	}
	t->name = std::to_string(currentTilePlacedOrder);
	map->setTileAtPos(pos.x, pos.y, t);
	currentTilePlacedOrder++;
}

bool TilePlacerComponent::canPlace(Vector2 pos)
{
	Tile* t = map->getTileAtPos(pos.x, pos.y);
	return t == nullptr || t->placeType == Tile::PlaceableOn::Everything ;
}
