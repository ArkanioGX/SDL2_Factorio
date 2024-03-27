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

	velocity = Vector2(hspd, vspd) * maxSpeed;


	if (inputState.mouse.getScrollWheel().y > 0) // scroll up
	{
		currentZoom = Maths::clamp(currentZoom + zoomSpeed, minZoom, maxZoom);
	}
	else if (inputState.mouse.getScrollWheel().y < 0) // scroll down
	{
		currentZoom = Maths::clamp(currentZoom - zoomSpeed, minZoom, maxZoom);
	}
	cam->setZoom(currentZoom);
}

void CameraControllerComponent::update(float dt)
{
	owner.setPosition(owner.getPosition() + (velocity * dt));
}
