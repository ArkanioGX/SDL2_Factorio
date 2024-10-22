#include "TilemapSpriteComponent.h"
#include "Tileset.h"
#include "Camera.h"

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
	for (Chunk* currentChunk : lastChunkRendered){
		for (int x = 0; x < ChunkSize; x++) {
			for (int y = 0; y < ChunkSize; y++) {
				Tile* currentTile = currentChunk->Tiles[x][y];
				if (currentTile != nullptr) {
					Vector2 tilePos = owner.getPosition() + (map->getPosGridToLocal(currentChunk->cx*ChunkSize+x, currentChunk->cy * ChunkSize + y) * owner.getScale());
					Rectangle tileRect = map->getRectFromID(currentTile->tileID);
					float rot = currentTile->rotation;
					renderer.drawSprite(tilePos, rot, owner.getScale(), texture, tileRect, Vector2::zero, Renderer::Flip::None);
				}
			}
		}
	}
}

void TilemapSpriteComponent::update(float dt)
{
	while (!lastChunkRendered.empty()) {
		Chunk* lChunk = lastChunkRendered.back();
		lastChunkRendered.pop_back();

		for (int x = 0; x < ChunkSize; x++) {
			for (int y = 0; y < ChunkSize; y++) {
				Tile* currentTile = lChunk->Tiles[x][y];
				if (currentTile != nullptr) {

					currentTile->isInRenderedChunk = false;
				}
			}
		}
		delete lChunk;
	}

	Vector2 camPos = Camera::mainCam->getPos();
	Vector2 gPos = map->getGridPosFromWorld(camPos.x, camPos.y) / ChunkSize;

	Vector2 currentChunkRadius = chunkRenderRadius / Camera::mainCam->getZoom();

	gPos = Vector2{
		Maths::clamp(gPos.x,currentChunkRadius.x,map->getMaxChunks().x - currentChunkRadius.x),
		Maths::clamp(gPos.y,currentChunkRadius.y,map->getMaxChunks().x - currentChunkRadius.y) };

	Vector2 minChunk = Vector2{ gPos.x - currentChunkRadius.x , gPos.y - currentChunkRadius.y };
	Vector2 maxChunk = Vector2{ gPos.x + currentChunkRadius.x , gPos.y + currentChunkRadius.y };

	for (int cx = minChunk.x; cx < maxChunk.x; cx++) {
		for (int cy = minChunk.y; cy < maxChunk.y; cy++) {
			Chunk* currentChunk = map->getChunk(cx, cy);
			lastChunkRendered.push_back(currentChunk);
			for (int x = 0; x < ChunkSize; x++) {
				for (int y = 0; y < ChunkSize; y++) {
					Tile* currentTile = currentChunk->Tiles[x][y];
					if (currentTile != nullptr) {

						currentTile->isInRenderedChunk = true;
					}
				}
			}
		}
	}
}

