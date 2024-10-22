#pragma once
#include "Tilemap.h"
#include "SpriteComponent.h"

class TilemapSpriteComponent : public SpriteComponent
{
public:
	TilemapSpriteComponent(Actor* ownerP, Tilemap* tmap , int drawOrderP = 100);
	~TilemapSpriteComponent() override;
	TilemapSpriteComponent() = delete;
	TilemapSpriteComponent(const TilemapSpriteComponent&) = delete;
	TilemapSpriteComponent& operator=(const TilemapSpriteComponent&) = delete;

	void draw(Renderer& renderer) override;
	void update(float dt) override;
private:
	Tilemap* map;

	Vector2 chunkRenderRadius = Vector2{ 2.5,2.5 };
	std::vector<Chunk*> lastChunkRendered;
};

const float TILEMAP_SIZE = 4.0f;