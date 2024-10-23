#include "TilePlacerRenderComponent.h"
#include "Tilemap.h"

TilePlacerRenderComponent::TilePlacerRenderComponent(Actor* ownerP, Tilemap* tmap, TilePlacerComponent* TPC, int drawOrderP):
	SpriteComponent(ownerP, Assets::getTexture("MachineTilesetAlpha"), drawOrderP),
	map(tmap),
	tpc(TPC)
{
	SDL_SetTextureAlphaMod(texture.toSDLTexture(), 100);
	
}

TilePlacerRenderComponent::~TilePlacerRenderComponent ()
{
}

void TilePlacerRenderComponent::draw(Renderer& renderer)
{


	for (PreviewTile pt : tpc->getPrevewTiles()) {

		Tile* currentTile = pt.tile;
		if (currentTile != nullptr) {
			Vector2 tilePos = owner.getPosition() + (map->getPosGridToLocal(pt.pos.x, pt.pos.y) * owner.getScale());
			Rectangle tileRect = map->getRectFromID(currentTile->tileID);
			float rot = currentTile->rotation;

			texture.toSDLTexture();

			renderer.drawSprite(tilePos, rot, owner.getScale(), texture, tileRect, Vector2::zero, Renderer::Flip::None);
		}
	}
}
