#pragma once
#include "Tilemap.h"
#include "SpriteComponent.h"

class TilemapSpriteComponent : public SpriteComponent
{
public:
	TilemapSpriteComponent(Actor* ownerP, Tilemap* tmap , int drawOrderP = 100);
	virtual ~TilemapSpriteComponent();
	TilemapSpriteComponent() = delete;
	TilemapSpriteComponent(const TilemapSpriteComponent&) = delete;
	TilemapSpriteComponent& operator=(const TilemapSpriteComponent&) = delete;

	void draw(Renderer& renderer) override;
private:
	Tilemap* map;
	Texture texture;
};

