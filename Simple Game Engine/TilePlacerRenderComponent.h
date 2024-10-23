#pragma once
#include "SpriteComponent.h"
#include "TilePlacerComponent.h"
class TilePlacerRenderComponent : public SpriteComponent
{
public:

	TilePlacerRenderComponent(Actor* ownerP, Tilemap* tmap, TilePlacerComponent* TPC, int drawOrderP = 100);
	virtual ~TilePlacerRenderComponent();

	void draw(Renderer& renderer) override;
	
	TilePlacerRenderComponent() = delete;
	TilePlacerRenderComponent(const TilePlacerRenderComponent&) = delete;
	TilePlacerRenderComponent& operator=(const TilePlacerRenderComponent&) = delete;

private:
	TilePlacerComponent* tpc;
	class Tilemap* map;
};

