#include "CameraControllerComponent.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Game.h"
#include "Actor.h"
#include <SDL.h>

CameraControllerComponent::CameraControllerComponent(Actor* ownerP) : Component(ownerP),
upKey(SDL_SCANCODE_W),
downKey(SDL_SCANCODE_S),
leftKey(SDL_SCANCODE_A),
rightKey(SDL_SCANCODE_D),
cam(Camera::mainCam),
velocity(Vector2::zero),
maxSpeed(500),
zoomSpeed(0.2)
{
}

void CameraControllerComponent::processInput(const InputState& inputState)
{
	int vspd = (inputState.keyboard.getKeyValue(SDL_SCANCODE_S)) - (inputState.keyboard.getKeyValue(SDL_SCANCODE_W));
	int hspd = (inputState.keyboard.getKeyValue(SDL_SCANCODE_D)) - (inputState.keyboard.getKeyValue(SDL_SCANCODE_A));

	velocity = Vector2(hspd, vspd) * (maxSpeed*(maxSpeedZoomMultiplier/currentZoom));


	if (inputState.mouse.getScrollWheel().y > 0) // scroll up
	{
		currentZoom = Maths::clamp(currentZoom + zoomSpeed, minZoom, maxZoom);
	}
	else if (inputState.mouse.getScrollWheel().y < 0) // scroll down
	{
		currentZoom = Maths::clamp(currentZoom - zoomSpeed, minZoom, maxZoom);
	}
	

}

void CameraControllerComponent::update(float dt)
{
	Vector2 camPos = owner.getPosition() + (velocity * dt);
	if (isClamped) {
		camPos.x = Maths::clamp(camPos.x, minClamp.x, maxClamp.x);
		camPos.y = Maths::clamp(camPos.y, minClamp.y, maxClamp.y);
	}
	owner.setPosition(camPos);
	cam->setZoom(Maths::SmoothDamp(cam->getZoom(),currentZoom,zoomV,0.2f,Maths::infinity,dt));
}

void CameraControllerComponent::setLimit(Vector2 min, Vector2 max)
{
	if (min == Vector2::null && max == Vector2::null) {
		isClamped = false;
	}
	else {
		isClamped = true;
		minClamp = min;
		maxClamp = max;
	}
}
