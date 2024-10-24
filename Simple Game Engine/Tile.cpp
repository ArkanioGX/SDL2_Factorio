#include "Tile.h"
#include "OreTile.h"
#include "Random.h"
#include "Tilemap.h"
#include "Renderer.h"

unsigned int Tile::seed = 0;

const Tile Tile::Null("Null",{-1}, 0, false, false, Type::Basic, Tile::PlaceableOn::Everything);

const Tile Tile::DGround("DesertGround",{1, 2, 3}, 0.0f, false, true, Type::Basic, Tile::PlaceableOn::Everything);
const Tile Tile::DWall("DesertWall",{4, 5, 6, 7}, 0.0f, false, false, Type::Basic, Tile::PlaceableOn::Nothing);
const Tile Tile::DWater("DesetWater",{8, 9}, 0.0f, false, false, Type::Basic, Tile::PlaceableOn::Everything);
const Tile Tile::DDeepWater("DesertDeepWater",{ 12, 13 }, 0.0f, false, false, Type::Basic, Tile::PlaceableOn::Everything);


void Tile::setRandomTID()
{
	Random::seed(seed);
	if (randomTileID) {
		tileID = tileIDlist[Random::getIntRange(0, tileIDlist.size() - 1)];
	}
	if (randomRotate) {
		rotation = Maths::piOver2 * Random::getIntRange(0, 3);
	}
	seed++;
}

Tile::~Tile()
{
}

Tile* Tile::copy()
{
	return new Tile(*this);
}


