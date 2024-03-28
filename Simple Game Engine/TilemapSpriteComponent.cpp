#include "TilemapSpriteComponent.h"
#include "Tileset.h"


TilemapSpriteComponent::TilemapSpriteComponent(Actor* ownerP, Tilemap* tmap, int drawOrderP):
	SpriteComponent(ownerP, tmap->getTexture(), drawOrderP),
	texture(tmap->getTexture()),
	map(tmap)
{
	Vector2 max = tmap->getTileset()->getTileRatio();
	ownerP->setScale(Vector2(max.y/max.x, 1));
}

TilemapSpriteComponent::~TilemapSpriteComponent()
{
}

void TilemapSpriteComponent::draw(Renderer& renderer)
{
	Vector2 max = map->getMaxTile();

	int tileNumberH = max.y;
	int tileNumberW = max.x;

	Vector2 origin = Vector2(map->getTexture().getWidth() / 2, map->getTexture().getHeight() / 2);

	for (int x = 0; x < tileNumberW; x++) {
		for (int y= 0; y < tileNumberH; y++) {

			Rectangle tileRect = map->getRectFromID(map->getTileIdAtPos(x, y));
			renderer.drawSprite(owner.getPosition() + (map->getPosGridToLocal(x,y) * owner.getScale()) , owner.getRotation(), owner.getScale(), texture, tileRect, origin, Renderer::Flip::None);
		}
	}
}

