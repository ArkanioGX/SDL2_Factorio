#include "MachineTileComponent.h"
#include "Log.h"
#include "MachineTile.h"

MachineTileComponent::MachineTileComponent(Actor* ownerP, Tilemap* tmap, int drawOrderP ) :
	SpriteComponent(ownerP,tmap->getTexture(), drawOrderP),
	map(tmap)
{
}

MachineTileComponent::~MachineTileComponent()
{
}

void MachineTileComponent::draw(Renderer& renderer)
{
	for (int i = 0; i < tileToDraw.size(); i++) {
		MachineTile* mt = tileToDraw[i];
		Vector2 tpos = (owner.getPosition() + map->getPosGridToLocal(mt->currentPos.x, mt->currentPos.y)) * owner.getScale();
		std::vector<ItemRenderContainer> irl = mt->additiveDraw();
		for (int i = 0; i < irl.size(); i++) {
			ItemRenderContainer irc = irl[i];
			Vector2 textureRatio = Vector2{ map->getTileset()->getTileRatio() };
			Vector2 tilePos = tpos + (irc.pos * map->getTileset()->getTileSize() * owner.getScale());
			renderer.drawSprite(tilePos, 0, owner.getScale() * textureRatio, irc.tex, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
		}
	}
}

void MachineTileComponent::addTileToDraw(MachineTile* mt)
{
	tileToDraw.push_back(mt);
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
		delete *mit;
		machineTileList.erase(mit);
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
	tileToDraw.clear();
	tileToUpdate.clear();
	tileToUpdate = machineTileList;

	while (!tileToUpdate.empty()) {
		MachineTile* currentTile = tileToUpdate[0];
		currentTile->update(dt);
	}
	
}
