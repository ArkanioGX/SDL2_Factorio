#include "MachineTileComponent.h"
#include "Log.h"

MachineTileComponent::MachineTileComponent(Actor* ownerP, Tilemap* tmap) :
	Component(ownerP),
	map(tmap)
{
}

void MachineTileComponent::addMTile(MachineTile* mt)
{
	machineTileList.push_back(mt);
	mt->ownerComponent = this;
}

void MachineTileComponent::removeMTile(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator mit = std::find(machineTileList.begin(), machineTileList.end(), mt);
	if (mit != machineTileList.end()) {
		machineTileList.erase(mit);
		//delete mt; TODO : To Implement
	}
	
}

void MachineTileComponent::tileUpdate(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator mit = std::find(tileToUpdate.begin(), tileToUpdate.end(), mt);
	if (mit != tileToUpdate.end()) {
		tileToUpdate.erase(mit);
	}
}

bool MachineTileComponent::tileAlreadyUpdated(MachineTile* mt)
{
	std::vector<MachineTile*>::iterator mit = std::find(tileToUpdate.begin(), tileToUpdate.end(), mt);
	return mit == tileToUpdate.end();
}

void MachineTileComponent::update(float dt)
{
	
	tileToUpdate.clear();
	tileToUpdate = machineTileList;

	Log::info(" === | === | === | === | === ");

	while (!tileToUpdate.empty()) {
		MachineTile* currentTile = tileToUpdate[0];
		currentTile->update(dt);
	}
	
	
}
