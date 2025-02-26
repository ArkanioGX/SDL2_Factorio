#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Component.h"
#include "Collision.h"
#include "Maths.h"

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector2::zero),
	scale(Vector2(1.0f,1.0f)),
	rotation(0.0f),
	game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor() {
	game.removeActor(this);
	while (!components.empty()) {
		delete components.back();
	}
}

void Actor::processInput(const InputState& inputState)
{
	if (state == Actor::ActorState::Active)
	{
		for (auto component : components)
		{
			component->processInput(inputState);
		}
		actorInput(inputState);
	}
}

void Actor::actorInput(const InputState& inputState)
{
}

const Vector2 Actor::getForward() const
{
	return Vector2(Maths::cos(rotation),-Maths::sin(rotation));
}

void Actor::setPosition(Vector2 positionP) {
	position = positionP;
}

void Actor::setScale(Vector2 scaleP)
{
	scale = scaleP;
}

void Actor::setScale(float scaleP) {
	scale = Vector2(scaleP, scaleP);
}


void Actor::setRotation(float rotationP) {
	rotation = rotationP;
}

void Actor::update(float dt) {
	if (state == ActorState::Active) {
		updateComponents(dt);
		updateActor(dt);
	}
}

void Actor::updateComponents(float dt) {
	for (auto component : components) {
		component->update(dt);
	}
}

void Actor::updateActor(float dt) {

}

void Actor::addComponent(Component* component) {
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); ++iter) {
		if (myOrder < (*iter)->getUpdateOrder()) {
			break;
		}
	}
	components.insert(iter, component);
}

void Actor::removeComponent(Component* component) {
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components)) {
		components.erase(iter);
	}
}

void Actor::OnTrigger(Collision* coll) {
	for (auto component : components) {
		component->OnTrigger(coll);
	}
}

