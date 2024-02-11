#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"
#include "Log.h"
#include "Game.h"

MoveComponent::MoveComponent(Actor* ownerP, Collider* coll, int updateOrderP) : 
	Component(ownerP,updateOrderP),
	velocity(Vector2::zero),
	angularSpeed(0.0f),
	collider(coll)
{
}

void MoveComponent::setVelocity(Vector2 velocityP)
{
	velocity = velocityP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed)) {
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(velocity.x) || !Maths::nearZero(velocity.y)) {
		Vector2 newPos = owner.getPosition() + velocity * dt;
		Vector2 oldPos = owner.getPosition();
		owner.setPosition({newPos.x, oldPos.y});
		//auto c = owner.GetComponent<Collider>();
		if (collider->checkCollision().size() != 0) { newPos.x = oldPos.x; }
		owner.setPosition(newPos);
		if (collider->checkCollision().size() != 0) { newPos.y = oldPos.y; }
		owner.setPosition(newPos);
	}
	
	
}

