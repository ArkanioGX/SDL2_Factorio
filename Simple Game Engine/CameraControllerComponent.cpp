#include "CameraControllerComponent.h"
#include <SDL_scancode.h>
#include "Log.h"
#include "Actor.h"
#include <SDL.h>

CameraControllerComponent::CameraControllerComponent(Actor* ownerP) : Component(ownerP),
upKey(SDL_SCANCODE_W),
downKey(SDL_SCANCODE_S),
leftKey(SDL_SCANCODE_A),
rightKey(SDL_SCANCODE_D),
cam(Camera::mainCam),
velocity(Vector2::zero),
maxSpeed(100),
zoomSpeed(0.1)
{
}

void CameraControllerComponent::processInput(const Uint8* keyState)
{
	int vspd = (keyState[downKey] == true) - (keyState[upKey] == true);
	int hspd = (keyState[rightKey] == true) - (keyState[leftKey] == true);

	velocity = Vector2(hspd, vspd) * maxSpeed;
	
	Log::info("Test");

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.wheel.y > 0) // scroll up
		{
			cam->setZoom(cam->getZoom() + zoomSpeed);
			Log::info("Up");
		}
		else if (event.wheel.y < 0) // scroll down
		{
			cam->setZoom(cam->getZoom() - zoomSpeed);
			Log::info("Down");
		}
		Log::info(std::to_string(event.wheel.y));
	}
}

void CameraControllerComponent::update(float dt)
{
	owner.setPosition(owner.getPosition() + (velocity * dt));
}
