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
	BuildMode currentBMode = tileToPlace->currentBMode[0];
	Vector2 gPos = map->getGridPosFromScreen(inputState.mouse.getPosition().x, inputState.mouse.getPosition().y);
	if (gPos != Vector2::null && inputState.mouse.getButtonState(1) == ButtonState::Pressed) {
		switch (currentBMode) {
		case BuildMode::Single:
			placePreviewTile(gPos);
			break;
		case BuildMode::StraightLine:
			beginLine = gPos;
			ComputeLinePos(gPos);
			break;
		}
		
	}
	else if (gPos != Vector2::null && inputState.mouse.getButtonState(1) == ButtonState::Held){
		switch (currentBMode) {
		case BuildMode::Single:
			placePreviewTile(gPos);
			break;
		case BuildMode::StraightLine:
			ComputeLinePos(gPos);
			break;
		}
	}
	else if (inputState.mouse.getButtonState(1) == ButtonState::Released) {
		lastTilePos = Vector2(-1, -1);
		beginLine = Vector2(-1, -1);
		lastEndLine = Vector2(-1, -1);
		pLineTileList.clear();
	}
	
	if (gPos != Vector2::null && inputState.mouse.getButtonState(3) == ButtonState::Pressed) {
		PreviewTile tp;
		tp.pos = gPos;
		std::vector<PreviewTile>::iterator tPlace = std::find(pTileList.begin(), pTileList.end(), tp);
		//Delete in the map if no tile found in preview at the position
		if (tPlace == pTileList.end()) {
			removeTile(gPos);
		}
		else {
			delete (*tPlace).tile;
			pTileList.erase(tPlace);
		}
		
	}

	if (inputState.keyboard.getKeyState(SDL_SCANCODE_RETURN) == ButtonState::Pressed) {
		confirmBuild();
	}

	if (inputState.keyboard.getKeyState(SDL_SCANCODE_Q) == ButtonState::Pressed) {
		currentRotation = ( currentRotation + 1) % 4 ;
	}
	if (inputState.keyboard.getKeyState(SDL_SCANCODE_E) == ButtonState::Pressed) {
		currentRotation = ( currentRotation - 1) % 4;
		if (currentRotation < 0) {
			currentRotation += 4;
		}
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

void TilePlacerComponent::confirmBuild()
{
	for (PreviewTile t : pTileList) {
		placeTile(t.pos, t.tile);
	}
	pTileList.clear();
}

void TilePlacerComponent::placePreviewTile(Vector2 pos)
{
	if (canPlace(pos) && pos != lastTilePos) {
		PreviewTile tp;
		lastTilePos = pos;
		tp.pos = pos;
		std::vector<PreviewTile>::iterator tPlace = std::find(pTileList.begin(), pTileList.end(), tp);
		if ( tPlace != pTileList.end()) {
			delete (*tPlace).tile;
			pTileList.erase(tPlace);
		}
		Tile* t = tileToPlace->copy();
		
		if (t->canRotate) {
			t->rotation = currentRotation * Maths::piOver2;
			t->rotateID = currentRotation % 4;
		}

		
		tp.tile = t;

		pTileList.push_back(tp);
	}
}

void TilePlacerComponent::ComputeLinePos(Vector2 pos)
{

	Vector2 line = pos - beginLine;
	int tileN = 0;
	//Line is horizontal
	if (abs(line.x) >= abs(line.y)) 
	{
		line.y = 0;
		tileN = abs(line.x);
	}
	else {
		line.x = 0;
		tileN = abs(line.y);
	}
	Vector2 tempEndLine = beginLine + line;
	
	if (tempEndLine != lastEndLine && line.length() > 0) {
		removeFromPreview(pLineTileList);
		Vector2 lineDir = line;
		lineDir.normalize();
		lastEndLine = tempEndLine;
		for (int i = 0; i < tileN; i++) {
			PreviewTile tp;
			tp.pos = beginLine + (lineDir*i);
			std::vector<PreviewTile>::iterator tPlace = std::find(pTileList.begin(), pTileList.end(), tp);
			if (tPlace != pTileList.end()) {
				delete (*tPlace).tile;
				pTileList.erase(tPlace);
			}
			Tile* t = tileToPlace->copy();

			if (t->canRotate) {
				if (lineDir.x != 0) {
					if (lineDir.x >= 0) {
						lastRotate = 2;
					}
					else {
						lastRotate = 0;
					}
				}
				else {
					if (lineDir.y >= 0) {
						lastRotate = 1;
					}
					else {
						lastRotate = 3;
					}
				}
				t->rotation = lastRotate * Maths::piOver2;
				t->rotateID = lastRotate;
				 
			}


			tp.tile = t;
			pLineTileList.push_back(tp);
			pTileList.push_back(tp);
		}
	}
	else if (tempEndLine != lastEndLine) {
		removeFromPreview(pLineTileList);
		Vector2 lineDir = line;
		lineDir.normalize();
		lastEndLine = tempEndLine;
		PreviewTile tp;
		tp.pos = beginLine;
		std::vector<PreviewTile>::iterator tPlace = std::find(pTileList.begin(), pTileList.end(), tp);
		if (tPlace != pTileList.end()) {
			delete (*tPlace).tile;
			pTileList.erase(tPlace);
		}
		Tile* t = tileToPlace->copy();
		if (t->canRotate) {
			t->rotation = lastRotate * Maths::piOver2;
			t->rotateID = lastRotate;
		}
		tp.tile = t;
		pLineTileList.push_back(tp);
		pTileList.push_back(tp);
	}
}

void TilePlacerComponent::placeTile(Vector2 pos, Tile* t)
{
	if (t->type == Tile::Type::Machine) {
		MachineTileComponent* mtc = owner.getComponent<MachineTileComponent*>();
		if (mtc != nullptr) {
			MachineTile* mt = static_cast<MachineTile*>(t);
			mt->ClearAllIO();
			mtc->addMTile(mt);
			mt->currentPos = pos;
			mt->connectToNearby();
			
		}
		Tile* tileAtPlace = map->getTileAtPos(pos.x, pos.y);
		if (tileAtPlace != nullptr) {
			if (tileAtPlace->type == Tile::Type::Machine) {
				mtc->removeMTile(static_cast<MachineTile*>(tileAtPlace));
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
	return t == nullptr || (t->placeType == Tile::PlaceableOn::Everything && *t != tileToPlace);
}

void TilePlacerComponent::removeTile(Vector2 pos)
{
	Tile* t = map->getTileAtPos(pos.x, pos.y);
	if (t != nullptr && t->type == Tile::Type::Machine) {
		MachineTileComponent* mtc = owner.getComponent<MachineTileComponent*>();
		if (mtc != nullptr) {
				mtc->removeMTile(static_cast<MachineTile*>(t));
		}
	}
	map->removeTileAtPos(pos.x, pos.y);
}

void TilePlacerComponent::clearPreview()
{
	while (!pTileList.empty()) {
		delete pTileList.back().tile;
		pTileList.pop_back();
	}
}

void TilePlacerComponent::removeFromPreview(std::vector<PreviewTile> ptl)
{
	
	for (int i = 0; i < ptl.size(); i++) {
		PreviewTile t = ptl[i];
		std::vector<PreviewTile>::iterator tPlace = std::find(pTileList.begin(), pTileList.end(), t);
		if (tPlace != pTileList.end()) {
			delete (*tPlace).tile;
			pTileList.erase(tPlace);
		}
	}
}

std::vector<PreviewTile> TilePlacerComponent::getPrevewTiles()
{
	return pTileList;
}
