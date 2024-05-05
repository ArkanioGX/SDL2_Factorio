#pragma once
#include "SpriteComponent.h"
#include "MachineTile.h"
#include "Tilemap.h"
#include <vector>


class MachineTileComponent : public SpriteComponent
{
private:
	std::vector<MachineTile*> machineTileList;

	std::vector<MachineTile*> tileToUpdate;



public:

	MachineTileComponent(class Actor* ownerP,Tilemap* tmap, int drawOrderP = 100);
	virtual ~MachineTileComponent();
	MachineTileComponent() = delete;
	MachineTileComponent(const MachineTileComponent&) = delete;
	MachineTileComponent& operator=(const MachineTileComponent&) = delete;

	void draw(Renderer& renderer) override;

	Tilemap* map;

	void addMTile(MachineTile* mt);
	void removeMTile(MachineTile* mt);

	void tileUpdate(MachineTile* mt);

	bool tileAlreadyUpdated(MachineTile* mt);

	void update(float dt) override;
};

