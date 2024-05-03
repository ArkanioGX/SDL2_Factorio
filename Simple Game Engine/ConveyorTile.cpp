#include "ConveyorTile.h"
#include "Log.h"
#include "MachineTileComponent.h"

const ConveyorTile ConveyorTile::base("baseConveyor",0,0.0f,true,1,2,false);

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
					else if ((mt->rotateID + 2) % 4 == rotateID) {
						addInput(mt);
						mt->addOutput(this);
					}
				}
			}
		}
	}


	Vector2 next;
	switch (rotateID) {
	case 0:
		next = Vector2(-1, 0);
		Log::info("Left");
		break;
	case 1:
		next = Vector2(0, 1);
		Log::info("Down");
		break;
	case 2:
		next = Vector2(1, 0);
		Log::info("Right");
		break;
	case 3:
		next = Vector2(0, -1);
		Log::info("Up");
		break;
	}
	Vector2 outPos = currentPos + next;
	Vector2 inPos = currentPos - next;
	
	if (m->isInsideMap(outPos)) {
		
	}
	if (m->isInsideMap(inPos)) {
		
		Tile* nextTile = m->getTileAtPos(inPos.x, inPos.y);
		if (nextTile != nullptr && nextTile->type == Type::Machine) {
			MachineTile* mt = static_cast<MachineTile*>(m->getTileAtPos(inPos.x, inPos.y));
			addInput(mt);
			mt->addOutput(this);
		}
	}
	//
}

void ConveyorTile::update(float dt)
{
	MachineTile::update(dt);
	Log::info(name);
}
