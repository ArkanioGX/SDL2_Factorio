#pragma once
#include "MoveComponent.h"
#include <SDL_stdinc.h>

class InputComponent : public MoveComponent
{
public:
	InputComponent(Actor* ownerP, Collider* coll);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void processInput(const Uint8* keyState);

	void setMaxSpeed(float maxSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);
	void setUpKey(int key);
	void setDownKey(int key);
	void setLeftKey(int key);
	void setRightKey(int key);

private:

	float maxSpeed;
	float maxAngularSpeed;

	int upKey;
	int downKey;
	int leftKey;
	int rightKey;
};

