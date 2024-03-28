#include "Camera.h"
#include "Actor.h"
#include "Game.h"

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

Vector2 Camera::getScreenPosInWorld(Vector2 pos)
{
	pos -= Vector2(WINDOW_WIDTH,WINDOW_HEIGHT) / 2;
	pos = pos / zoom;
	Vector2 worldPos = (pos + owner.getPosition() );
	//Log::info("X : " + std::to_string(worldPos.x) + " | Y : " + std::to_string(worldPos.y));
	return worldPos;
}
