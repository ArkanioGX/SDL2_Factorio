#include "TilemapSpriteComponent.h"


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
	
	

	int tileNumberH = max.y;
	int tileNumberW = max.x;
	for (int y = 0; y < tileNumberH; y++) {
		for (int x = 0; x < tileNumberW; x++) {
			
			renderer.drawSprite(owner.getPosition() + map->getPosGridToLocal(x,y), owner.getRotation(),owner.getScale(),texture, map->getRectFromID(map->getTileIdAtPos(x,y)), Vector2::zero, Renderer::Flip::None);
		}
	}
}

