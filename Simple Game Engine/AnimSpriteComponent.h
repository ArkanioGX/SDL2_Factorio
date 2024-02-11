#pragma once
#include <vector>
#include "SpriteComponent.h"
using std::vector;
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* ownerP, Texture& textureP, int drawOrderP = 100, int tileSize = 16);
	virtual ~AnimSpriteComponent();
	AnimSpriteComponent() = delete;
	AnimSpriteComponent(const AnimSpriteComponent&) = delete;
	AnimSpriteComponent& operator=(const AnimSpriteComponent&) = delete;

	float getAnimFps() const { return animFPS; }
	void setAnimFPS(float animFPSP);

	void update(float dt);

private:
	vector<Rectangle> rectList;
	float currentFrame;
	float animFPS;

	int size;

	Rectangle getRectFromFrame(int id);
};

