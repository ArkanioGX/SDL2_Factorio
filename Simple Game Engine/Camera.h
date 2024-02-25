#pragma once
#include "Component.h"
#include "Vector2.h"
#include "Maths.h"

class Camera : public Component
{
private:
	float zoom;
public:
	static Camera* mainCam;

	Camera(Actor* ownerP, Vector2 posP = Vector2::zero, float zoomP = 1);
	virtual ~Camera();
	Camera() = delete;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	Vector2 getPos();
	float getZoom() const { return zoom; }

	void setZoom(float z);
};

