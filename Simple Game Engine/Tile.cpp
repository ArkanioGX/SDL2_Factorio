#include "Tile.h"
#include "OreTile.h"


const Tile Tile::Null(-1,0,false, Type::Basic, Tile::PlaceableOn::Nothing);

const Tile Tile::Ground(0,0.0f, false,Type::Basic, Tile::PlaceableOn::Everything);
const Tile Tile::Wall(1, 0.0f, false, Type::Basic, Tile::PlaceableOn::Nothing);
const Tile Tile::Water(3, 0.0f, false, Type::Basic, Tile::PlaceableOn::Everything);


