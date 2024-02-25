#pragma once
#include "Component.h"
#include "Camera.h"


class CameraControllerComponent : public Component
{
public:
	CameraControllerComponent(Actor* ownerP);
	CameraControllerComponent() = delete;
	CameraControllerComponent(const CameraControllerComponent&) = delete;
	CameraControllerComponent& operator=(const CameraControllerComponent&) = delete;

	void processInput(const Uint8* keyState);

	void update(float dt);

private:

	Vector2 velocity;
	float maxSpeed;
	float zoomSpeed;

	int upKey;
	int downKey;
	int leftKey;
	int rightKey;

	Camera* cam;
};

