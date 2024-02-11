#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"


SpriteComponent::SpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP, Rectangle rP) :
	Component(ownerP),
	texture(textureP),
	drawOrder(drawOrderP),
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight()),
	rect(rP)
{
	owner.getGame().getRenderer().addSprite(this);

}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(Renderer& renderer)
{
	Vector2 origin{ texWidth / 2.f, texHeight / 2.f };
	renderer.drawSprite(owner, texture, rect, origin, Renderer::Flip::None);
}
