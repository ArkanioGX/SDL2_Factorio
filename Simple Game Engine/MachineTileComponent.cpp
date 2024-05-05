#include "MachineTileComponent.h"
#include "Log.h"

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
	for (int i = 0; i < machineTileList.size(); i++) {
		MachineTile* mt = machineTileList[i];
		Vector2 tpos = (owner.getPosition() + map->getPosGridToLocal(mt->currentPos.x, mt->currentPos.y)) * owner.getScale();
		std::vector<ItemRenderContainer> irl = mt->additiveDraw();
		ItemRenderContainer irc = irl[0];
		Vector2 textureRatio = Vector2{map->getTileset()->getTileRatio()};
		Vector2 tilePos = tpos + (irc.pos * map->getTileset()->getTileSize() * owner.getScale());
		renderer.drawSprite(tilePos, 0, owner.getScale() * textureRatio, irc.tex, Rectangle::nullRect, Vector2::zero, Renderer::Flip::None);
	}
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
