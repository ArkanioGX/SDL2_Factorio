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

	void processInput(const struct InputState& inputState) override;

	void update(float dt);

	void setLimit(Vector2 min, Vector2 max);

private:

	Vector2 velocity;
	float maxSpeed;
	float maxSpeedZoomMultiplier = 1.2;
	float zoomSpeed;

	int upKey;
	int downKey;
	int leftKey;
	int rightKey;

	Camera* cam;

	float currentZoom = 1;
	float minZoom = 0.1;
	float maxZoom = 2;

	bool isClamped = false;
	Vector2 minClamp = Vector2::null;
	Vector2 maxClamp = Vector2::null;
};

