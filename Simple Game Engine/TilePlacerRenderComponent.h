#pragma once
#include "SpriteComponent.h"
class TilePlacerRenderComponent : public SpriteComponent
{
	TilePlacerRenderComponent(Actor* ownerP, Texture& textureP, int drawOrderP = 100, int tileSize = 16);
	virtual ~TilePlacerRenderComponent();
	TilePlacerRenderComponent() = delete;
	TilePlacerRenderComponent(const TilePlacerRenderComponent&) = delete;
	TilePlacerRenderComponent& operator=(const TilePlacerRenderComponent&) = delete;
};

