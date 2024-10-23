#include "ConveyorTile.h"
#include "Log.h"
#include "MachineTileComponent.h"

const ConveyorTile ConveyorTile::base("baseConveyor",0,0.0f,true,1,2,false);
const ConveyorTile ConveyorTile::upgrade("upgradedConveyor", 0, 0.0f, true, 4, 4, false);

ConveyorTile::~ConveyorTile()
{
	MachineTile::~MachineTile();
	while (!itemCList.empty()) {
		delete itemCList.back();
		itemCList.pop_back();
	}
}

void ConveyorTile::init()
{
	itemCList.clear();
	for (int i = 0; i < itemSize; i++) {
		float bt = (1 / float(itemSize)) * ((itemSize-1)-i);
		ItemContainer* ic;
		ic = new ItemContainer{ Item::None,bt,0.0f,itemSize,false,2 };
		
		itemCList.push_back(ic);
	}
}

Tile* ConveyorTile::copy()
{
	return new ConveyorTile(*this);
}

void ConveyorTile::connectToNearby()
{
	Tilemap* m = ownerComponent->map;
	for (int r = 0; r < 4; r++) {
		Vector2 next = getPosFromSide(r);
		Vector2 nextPos = currentPos + next;
		if (m->isInsideMap(nextPos)) {
			Tile* nextTile = m->getTileAtPos(nextPos.x, nextPos.y);
			if (nextTile != nullptr && nextTile->type == Type::Machine)
			{ 
				MachineTile* tileToCheck = static_cast<MachineTile*>(nextTile);
				if (r == rotateID) {
					//Same way of the conveyor
					if (tileToCheck->canConnect(r, IOType::Input,this)) {
						addOutput(tileToCheck);
						tileToCheck->addInput(this);
					}
				}
				else {
					//Border and back of the conveyor
					if (tileToCheck->canConnect(r, IOType::Output,this)) {
						addInput(tileToCheck);
						tileToCheck->addOutput(this);
					}
				}
			}
		}
	}
}

/// <summary>
/// Check if the tile can connect from this side
/// </summary>
/// <param name="side">: Side of the I/O from the tile asking </param>
/// <param name="io">: If the question is about being an input or an output of the tile </param>
/// <returns>If the connection is successful </returns>
bool ConveyorTile::canConnect(int side, IOType io,MachineTile* mt)
{
	switch (io) {
		case IOType::Input:
			return (side != ((rotateID + 2) % 4));
		break;
		case IOType::Output:
			return (side == ((rotateID + 2) % 4));
		break;
	}
	return false;
}

void ConveyorTile::update(float dt)
{
	MachineTile::update(dt);
	for (int i = 0; i < itemCList.size(); i++) {
		ItemContainer* icl = itemCList[i];
		if (icl->hasItem()) {
			if (!icl->isBlocked) {
				icl->t = icl->t + dt * speed;
			}
			if (icl->t >= 1) {
				if (nextItemContainer(i)) {
					icl->t = 0;
					icl->item = Item::None;
					icl->isBlocked = false;
				}
				else {
					icl->isBlocked = true;
					icl->t = 1;
				}
			}
		}
	}
}



std::vector<ItemRenderContainer> ConveyorTile::additiveDraw()
{
	std::vector<ItemRenderContainer> ircl;
	

	Vector2 endPos;
	switch (rotateID) {
	case 0:
		endPos = Vector2(-0.5, 0.5);
		break;
	case 1:
		endPos = Vector2(0.5, 1.5);
		break;
	case 2:
		endPos = Vector2(1.5, 0.5);
		break;
	case 3:
		endPos = Vector2(0.5, -0.5);
		break;
	}

	Vector2 midPos = Vector2(0.5, 0.5);

	
	

	
	for (int i = 0; i < itemCList.size(); i++) {
		ItemRenderContainer ItemToRender;
		ItemContainer* ic = itemCList[i];
		if (ic->hasItem()) {
			ItemToRender.tex = ic->item.texture;

			Vector2 startPos;
			switch (ic->inSide) {
			case 0:
				startPos = Vector2(-0.5, 0.5);
				break;
			case 1:
				startPos = Vector2(0.5, 1.5);
				break;
			case 2:
				startPos = Vector2(1.5, 0.5);
				break;
			case 3:
				startPos = Vector2(0.5, -0.5);
				break;
			}

			float newT = ic->baseT + (ic->t / ic->iSize);

			Vector2 newPos;

			if (newT <= 0.5) {
				newPos = Vector2::lerp(startPos, midPos, (newT * 2));
			}
			else {
				newPos = Vector2::lerp(midPos, endPos, ((newT - 0.5) * 2));
			}

			ItemToRender.pos = newPos;



			ircl.push_back(ItemToRender);
		}
	}
	return ircl;
}

bool ConveyorTile::giveItem(ItemContainer* it, int side)
{
	ItemContainer* ic = itemCList[itemCList.size() - 1];
	if (!ic->hasItem()) {
		ic->t = it->t - 1;
		ic->inSide = (side + 2) % 4;
		ic->item = it->item;
		return true;
	}
	return false;
}

bool ConveyorTile::nextItemContainer(int contId)
{
	if (contId == 0) {
		if (outputTile.size() > 0) {
			return outputTile[0]->giveItem(itemCList[contId], rotateID);
		}
		return false;
	}
	else {
		int newCID = contId - 1;
		ItemContainer* ic = itemCList[newCID];
		if (ic->hasItem()) {
			return false;
		}
		else {
			ic->t = itemCList[contId]->t - 1;
			ic->inSide = itemCList[contId]->inSide;
			ic->item = itemCList[contId]->item;
			itemCList[contId]->item = Item::None;
			return true;
		}
	}
}
