#include "MachineTile.h"
#include "MachineTileComponent.h"

void MachineTile::connectToNearby()
{

}

bool MachineTile::canConnect(int side, IOType io, MachineTile* mt)
{
	return false;
}

MachineTile::~MachineTile()
{
	ClearAllIO();
}

Tile* MachineTile::copy()
{
	return new MachineTile(*this);
}

void MachineTile::update(float dt)
{
	ownerComponent->tileUpdate(this);
	for (int i = 0; i < outputTile.size(); i++) {
		if (!ownerComponent->tileAlreadyUpdated(outputTile[i])) {
			outputTile[i]->update(dt);
		}
	}
	ownerComponent->addTileToDraw(this);
}

std::vector<ItemRenderContainer> MachineTile::additiveDraw()
{
	std::vector<ItemRenderContainer> ircl;
	return ircl;
}

bool MachineTile::giveItem(ItemContainer* it, int side = 0)
{
	return true;
}

void MachineTile::addInput(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator it = std::find(inputTile.begin(), inputTile.end(), mt);
	if (it == inputTile.end()) {
		inputTile.push_back(mt);
	}
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
	std::vector<MachineTile*>::iterator it = std::find(outputTile.begin(), outputTile.end(), mt);
	if (it == outputTile.end()) {
		outputTile.push_back(mt);
	}
}

void MachineTile::removeOutput(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator it = std::find(outputTile.begin(), outputTile.end(), mt);
	while (it != outputTile.end()) {
		outputTile.erase(it);
		it = std::find(outputTile.begin(), outputTile.end(), mt);
	}
}


/// <summary>
/// Clears all reference if this tile in others to avoid call to an inexistant tile
/// </summary>
void MachineTile::ClearAllIO()
{
	while (!inputTile.empty()) {
		MachineTile* tileToRemove = inputTile.back();
		tileToRemove->removeOutput(this);
		removeInput(tileToRemove);
	}
	while (!outputTile.empty()) {
		MachineTile* tileToRemove = outputTile.back();
		tileToRemove->removeInput(this);
		removeOutput(tileToRemove);
	}
}

