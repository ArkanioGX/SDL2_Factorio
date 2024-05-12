#include "ConveyorTile.h"
#include "Log.h"
#include "MachineTileComponent.h"

const ConveyorTile ConveyorTile::base("baseConveyor",0,0.0f,true,1,2,false);
const ConveyorTile ConveyorTile::upgrade("upgradedConveyor", 0, 0.0f, true, 1, 4, false);

void ConveyorTile::init()
{
	itemCList.clear();
	for (int i = 0; i < itemSize; i++) {
		float bt = (1 / float(itemSize)) * ((itemSize-1)-i);
		ItemContainer* ic = new ItemContainer{ Item::Test,bt,0.0f,itemSize,false,2 };
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
		Vector2 next;
		switch (r) {
		case 0:
			next = Vector2(-1, 0);
			break;
		case 1:
			next = Vector2(0, 1);
			break;
		case 2:
			next = Vector2(1, 0);
			break;
		case 3:
			next = Vector2(0, -1);
			break;
		}
		Vector2 nextPos = currentPos + next;
		if (m->isInsideMap(nextPos)) {
			Tile* nextTile = m->getTileAtPos(nextPos.x, nextPos.y);
			if (r == rotateID) {
				if (nextTile != nullptr && nextTile->type == Type::Machine) {
					MachineTile* mt = static_cast<MachineTile*>(m->getTileAtPos(nextPos.x, nextPos.y));
					if (mt->multiInput) {
						addOutput(mt);
						mt->addInput(this);
					}
					else if ((mt->rotateID+2)%4 != rotateID){ //If not in the counter way
						addOutput(mt);
						mt->addInput(this);
					}
				}
			}
			else {
				if (nextTile != nullptr && nextTile->type == Type::Machine) {
					MachineTile* mt = static_cast<MachineTile*>(m->getTileAtPos(nextPos.x, nextPos.y));
					if (mt->multiInput) {
						addInput(mt);
						mt->addOutput(this);
					}
					else if ((mt->rotateID + 2) % 4 == r) {
						addInput(mt);
						mt->addOutput(this);
					}
				}
			}
		}
	}
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
					if (outputTile.size() == 0) { //TODO : Remove later
						icl->t = 0;
						icl->item = Item::None;
					}
					else {
						icl->isBlocked = true;
						icl->t = 1;
					}

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
		it->item = Item::None;
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
			ic->inSide = (rotateID + 2) % 4;
			ic->item = itemCList[contId]->item;
			itemCList[contId]->item = Item::None;
			return true;
		}
	}
}
