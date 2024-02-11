#pragma once
#include "Collider.h"
#include "Actor.h"


class Collision
{
public:
	Collision(Actor* h, Collider* c);

	Collision() = delete;
	Collision(const Collision&) = delete;
	Collision& operator=(const Collision&) = delete;

	Actor* hit;
	Collider* coll;
};