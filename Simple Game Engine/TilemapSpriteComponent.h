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
private:
	Tilemap* map;

	
};

const float TILEMAP_SIZE = 4.0f;