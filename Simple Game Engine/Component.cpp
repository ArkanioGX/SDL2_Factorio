#include "Component.h"
#include "Collision.h"
#include "Actor.h"
#include <string>

Component::Component(Actor* ownerP, int updateOrderP) : owner(*ownerP), updateOrder(updateOrderP) {
	owner.addComponent(this);
}

Component::~Component() {
	owner.removeComponent(this);
}

void Component::update(float dt) {

}

void Component::processInput(const Uint8* keyState)
{
}

void Component::OnTrigger(Collision* coll)
{
}
