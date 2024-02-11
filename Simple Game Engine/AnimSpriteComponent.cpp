#include "AnimSpriteComponent.h"
#include "Log.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP, int tileSize) :
	SpriteComponent(ownerP, textureP, drawOrderP, Rectangle::nullRect),
	currentFrame(0.0f),
	animFPS(12.0f),
	size(tileSize)
{
	int nRow = texture.getWidth() / size;
	int nColl = texture.getHeight() / size;

	int lastFrame = nRow * nColl;

	for (int i = 0; i < lastFrame; i++) {
		Rectangle r = getRectFromFrame(i);
		rectList.push_back(r);
	}
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::setAnimFPS(float animFPSP)
{
	animFPS = animFPSP;
}

void AnimSpriteComponent::update(float dt)
{
	SpriteComponent::update(dt);
	if (rectList.size() > 0) {
		currentFrame += animFPS * dt;
		while (currentFrame >= rectList.size()) {
			currentFrame -= rectList.size();
		}
		rect = getRectFromFrame(currentFrame);
	}
}

Rectangle AnimSpriteComponent::getRectFromFrame(int id) {
	int nRow = texture.getWidth() / size;

	float x = int(id % nRow) * size;
	float y = int(id / nRow) * size;

	return { x,y,float(size),float(size) };
}
