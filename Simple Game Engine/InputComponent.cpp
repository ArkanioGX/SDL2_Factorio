#include "InputComponent.h"
#include <SDL_scancode.h>

InputComponent::InputComponent(Actor* ownerP, Collider* coll):
	MoveComponent(ownerP, coll),
	maxSpeed(100.f),
	maxAngularSpeed(1.f),
	upKey(SDL_SCANCODE_W),
	downKey(SDL_SCANCODE_S),
	leftKey(SDL_SCANCODE_A),
	rightKey(SDL_SCANCODE_D)
{
}

void InputComponent::processInput(const Uint8* keyState)
{
	float vSpeed = (keyState[downKey] == true) - (keyState[upKey] == true);
	float hSpeed = (keyState[rightKey] == true) - (keyState[leftKey] == true);

	setVelocity({ hSpeed * maxSpeed ,vSpeed * maxSpeed });
}

void InputComponent::setMaxSpeed(float maxSpeedP)
{
	maxSpeed = maxSpeedP;
}

void InputComponent::setMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::setUpKey(int key)
{
	upKey = key;
}

void InputComponent::setDownKey(int key)
{
	downKey = key;
}

void InputComponent::setLeftKey(int key)
{
	leftKey = key;
}

void InputComponent::setRightKey(int key)
{
	rightKey = key;
}




