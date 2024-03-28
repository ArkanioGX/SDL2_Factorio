#include "Tile.h"

const Tile Tile::Null(-1,0,Tile::PlaceableOn::Nothing);

const Tile Tile::Ground(0,0.0f, Tile::PlaceableOn::Everything);
const Tile Tile::Wall(1, 0.0f, Tile::PlaceableOn::Nothing);
const Tile Tile::Ore(2, 0.0f, Tile::PlaceableOn::Everything);
const Tile Tile::Water(3, 0.0f, Tile::PlaceableOn::OnlyTransport);
