#include "InventoryTile.h"
#include "MachineTileComponent.h"


InventoryTile::InventoryTile() : MachineTile()
{
    
}

InventoryTile::InventoryTile(std::string tname):
    MachineTile(tname, 3, 0, false)
{
    
}

InventoryTile::InventoryTile(const InventoryTile& other) :
    MachineTile(other.tileName, other.tileID, other.rotation, other.canRotate)
{
    
}

Tile* InventoryTile::copy()
{
    return new InventoryTile(*this);
}

bool InventoryTile::giveItem(ItemContainer* it, int side)
{
    return true;
}

void InventoryTile::connectToNearby()
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
				if (tileToCheck->canConnect(r, IOType::Output, this)) {
					addInput(tileToCheck);
					tileToCheck->addOutput(this);
				}
			}
		}
	}
}

bool InventoryTile::canConnect(int side, IOType io, MachineTile* mt)
{
	return io == IOType::Input;
}

const InventoryTile InventoryTile::baseInventory("baseInventory");