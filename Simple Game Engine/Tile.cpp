#include "Tile.h"
#include "OreTile.h"
#include "Random.h"

unsigned int Tile::seed = 0;

const Tile Tile::Null({-1}, 0, false, Type::Basic, Tile::PlaceableOn::Nothing);

const Tile Tile::DGround({0,1,2,3},0.0f, false,Type::Basic, Tile::PlaceableOn::Everything);
const Tile Tile::DWall({4,5,6,7}, 0.0f, false, Type::Basic, Tile::PlaceableOn::Nothing);
const Tile Tile::DWater({8,9}, 0.0f, false, Type::Basic, Tile::PlaceableOn::Everything);
const Tile Tile::DDeepWater({ 12,13 }, 0.0f, false, Type::Basic, Tile::PlaceableOn::Everything);

void Tile::setRandomTID()
{
	if (randomTileID) {
		Random::seed(seed);
		tileID = tileIDlist[Random::getIntRange(0, tileIDlist.size() - 1)];
		seed++;
	}
}
