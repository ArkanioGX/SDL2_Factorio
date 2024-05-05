#include "MachineTile.h"
#include "MachineTileComponent.h"

void MachineTile::connectToNearby()
{

}

MachineTile::~MachineTile()
{
}

Tile* MachineTile::copy()
{
	return new MachineTile(*this);
}

void MachineTile::update(float dt)
{
	for (int i = 0; i < outputTile.size(); i++) {
		if (!ownerComponent->tileAlreadyUpdated(outputTile[i])) {
			outputTile[i]->update(dt);
		}
	}
	ownerComponent->tileUpdate(this);
}

std::vector<ItemRenderContainer> MachineTile::additiveDraw()
{
	std::vector<ItemRenderContainer> ircl;
	return ircl;
}

bool MachineTile::giveItem(ItemContainer* it)
{
	return true;
}

void MachineTile::addInput(MachineTile* mt)
{
	inputTile.push_back(mt);
}

void MachineTile::removeInput(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator it = std::find(inputTile.begin(), inputTile.end(), mt);
	while (it != inputTile.end()) {
		inputTile.erase(it);
		it = std::find(inputTile.begin(), inputTile.end(), mt);
	}
}

void MachineTile::addOutput(MachineTile* mt)
{
	outputTile.push_back(mt);
}

void MachineTile::removeOutput(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator it = std::find(outputTile.begin(), outputTile.end(), mt);
	while (it != outputTile.end()) {
		outputTile.erase(it);
		it = std::find(outputTile.begin(), outputTile.end(), mt);
	}
}

