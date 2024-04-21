#include "MachineTile.h"
#include "MachineTileComponent.h"

void MachineTile::update(float dt, MachineTileComponent* msc)
{
	for (int i = 0; i < outputTile.size(); i++) {
		if (!msc->tileAlreadyUpdated(outputTile[i])) {
			outputTile[i]->update(dt, msc);
		}
	}
	msc->tileUpdate(this);
}

void MachineTile::additiveDraw()
{
}

