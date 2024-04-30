#include "ConveyorTile.h"
#include "Log.h"

const ConveyorTile ConveyorTile::base("baseConveyor",0,0.0f,true,1,2);

Tile* ConveyorTile::copy()
{
	return new ConveyorTile(*this);
}

void ConveyorTile::update(float dt)
{
	MachineTile::update(dt);
	Log::info(name);
}
