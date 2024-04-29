#include "ConveyorTile.h"
#include "Log.h"

const ConveyorTile ConveyorTile::base(0,0.0f,true,1,2);

void ConveyorTile::update(float dt)
{
	MachineTile::update(dt);
	Log::info(name);
}
