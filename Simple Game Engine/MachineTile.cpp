#include "MachineTile.h"
#include "MachineTileComponent.h"

void MachineTile::update(float dt)
{
	for (int i = 0; i < outputTile.size(); i++) {
		if (!ownerComponent->tileAlreadyUpdated(outputTile[i])) {
			outputTile[i]->update(dt);
		}
	}
	ownerComponent->tileUpdate(this);
}

void MachineTile::additiveDraw()
{
}

