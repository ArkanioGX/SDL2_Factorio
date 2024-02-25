#include "Camera.h"
#include "Actor.h"

Camera* Camera::mainCam = nullptr;

Camera::Camera(Actor* ownerP, Vector2 posP, float zoomP) :Component(ownerP), zoom(zoomP)
{
	if (mainCam == nullptr) {
		mainCam = this;
	}
	owner.setPosition(posP);
}

Vector2 Camera::getPos() { return owner.getPosition(); }

void Camera::setZoom(float z) { zoom = z; }

Camera::~Camera()
{
}
