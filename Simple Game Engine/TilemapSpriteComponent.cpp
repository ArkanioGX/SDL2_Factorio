#include "TilemapSpriteComponent.h"
#include "Log.h"

TilemapSpriteComponent::TilemapSpriteComponent(Actor* ownerP, Tilemap* tmap, int drawOrderP):
	SpriteComponent(ownerP, tmap->getTexture(), drawOrderP),
	texture(tmap->getTexture()),
	map(tmap)
{
}

TilemapSpriteComponent::~TilemapSpriteComponent()
{
}

void TilemapSpriteComponent::draw(Renderer& renderer)
{
	Vector2 max = map->getMaxTile();
	
	Log::info(std::to_string(max.x));

	int tileNumberH = max.y;
	int tileNumberW = max.x;
	for (int y = 0; y < tileNumberH; y++) {
		for (int x = 0; x < tileNumberW; x++) {
			
			renderer.drawSprite(owner.getPosition() + map->getPosGridToLocal(x,y), owner.getRotation(),owner.getScale(),texture, map->getRectFromID(map->getTileIdAtPos(x,y)), Vector2::zero, Renderer::Flip::None);
		}
	}
}

