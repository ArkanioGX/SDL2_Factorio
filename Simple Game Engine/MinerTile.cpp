#include "MinerTile.h"

MinerTile::MinerTile(): MachineTile(),oreMultiplier(0)
{
}

MinerTile::MinerTile(std::string tname, int tID, float om):
    MachineTile(tname, tID, 0, false, true),
    oreMultiplier(om)
{
}

MinerTile::MinerTile(const MinerTile& other):
    MachineTile(other.tileName, other.tileID, other.rotation, other.canRotate, other.multiInput),
    oreMultiplier(other.oreMultiplier)
{
    
}

Tile* MinerTile::copy()
{
    return new MinerTile(*this);
}

bool MinerTile::giveItem(ItemContainer* it, int side)
{
    return false;
}
