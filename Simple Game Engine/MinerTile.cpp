#include "MinerTile.h"
#include "MachineTileComponent.h"

const MinerTile MinerTile::baseMiner("baseMiner", 2, 1.0f);

//TODO : Better ConnectNearby();

MinerTile::MinerTile(): MachineTile(),oreMultiplier(0)
{
	init();
}

MinerTile::MinerTile(std::string tname, int tID, float om):
    MachineTile(tname, tID, 0, false),
    oreMultiplier(om)
{
	init();
}

MinerTile::MinerTile(const MinerTile& other):
    MachineTile(other.tileName, other.tileID, other.rotation, other.canRotate),
    oreMultiplier(other.oreMultiplier)
{
	init();
}

void MinerTile::init()
{
	itemCreator = new ItemContainer{ Item::Silver,0,0.0f,0,false,2 };
}

Tile* MinerTile::copy()
{
    return new MinerTile(*this);
}

void MinerTile::update(float dt)
{
	MachineTile::update(dt);
	if (itemCreator->t >= 1) {
		if (outputTile.size() > 0) {
			if (outputTile[0]->giveItem(itemCreator,0)) {
				itemCreator->t = itemCreator->t-1;
				itemCreator->item = Item(Item::Silver);
				itemCreator->isBlocked = false;
			}
			else {
				itemCreator->isBlocked = true;
				itemCreator->t = 1;
			}
		}
	}
	else {
		if (!itemCreator->isBlocked) {
			itemCreator->t = itemCreator->t + (dt * oreMultiplier);
		}
	}
	
}

bool MinerTile::giveItem(ItemContainer* it, int side)
{
    return false;
}

void MinerTile::connectToNearby()
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
				if (tileToCheck->canConnect(r, IOType::Input,this)) {
					addOutput(tileToCheck);
					tileToCheck->addInput(this);
					ReceivingTile.push_back(IOTile{ tileToCheck,r });
				}
			}
		}
	}
}

bool MinerTile::canConnect(int side, IOType io, MachineTile* mt)
{
	bool isOutput = io == IOType::Output;
	if (isOutput) {
		ReceivingTile.push_back(IOTile{ mt,side });
	}
	return isOutput;
}
