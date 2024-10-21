#include "TilemapSpriteComponent.h"
#include "Tileset.h"


TilemapSpriteComponent::TilemapSpriteComponent(Actor* ownerP, Tilemap* tmap, int drawOrderP):
	SpriteComponent(ownerP, tmap->getTexture(), drawOrderP),
	map(tmap)
{
	Vector2 max = tmap->getTileset()->getTileRatio();
	ownerP->setScale(Vector2(TILEMAP_SIZE/max.x, TILEMAP_SIZE/max.y));
}

TilemapSpriteComponent::~TilemapSpriteComponent()
{
}

void TilemapSpriteComponent::draw(Renderer& renderer)
{
	Vector2 max = map->getMaxChunks();

	int tileNumberH = max.y;
	int tileNumberW = max.x;

	for (int x = 0; x < tileNumberW; x++) {
		for (int y= 0; y < tileNumberH; y++) {
			Tile* currentTile = map->getTileAtPos(x, y);
			if (currentTile != nullptr) {
				Vector2 tilePos = owner.getPosition() + (map->getPosGridToLocal(x, y) * owner.getScale());
				Rectangle tileRect = map->getRectFromID(currentTile->tileID);
				float rot = currentTile->rotation;
				renderer.drawSprite(tilePos, rot, owner.getScale(), texture, tileRect, Vector2::zero, Renderer::Flip::None);
				
			}
		}
	}
}

