#pragma once
#include "Component.h"
#include "MachineTile.h"
#include <vector>


class MachineTileComponent : public Component
{
private:
	std::vector<MachineTile*> machineTileList;

	std::vector<MachineTile*> tileToUpdate;

public:

	MachineTileComponent(class Actor* ownerP);

	void addMTile(MachineTile* mt);
	void removeMTile(MachineTile* mt);

	void tileUpdate(MachineTile* mt);

	bool tileAlreadyUpdated(MachineTile* mt);

	void update(float dt) override;
};

