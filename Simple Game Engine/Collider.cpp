#include "Collider.h"
#include "Collision.h"
#include "Log.h"

std::vector<Collider*> Collider::collList = {};

Collider::Collider(Actor* ownerP, Rectangle r, bool CPT = false) : Component(ownerP)
{
	canPassThrough = CPT;
	addCollider(this);

	crect = r;
	
}

Collider::~Collider()
{
	removeCollider(this);
}

std::vector<Collision*> Collider::checkCollision()
{
	std::vector<Collision*> list = {};
	for (Collider* c : collList)
	{
		if (c != this && !c->canPassThrough) {
			Rectangle r1 = { owner.getPosition().x + crect.x ,owner.getPosition().y + crect.y,crect.width,crect.height};
			Rectangle r2 = { c->getActor()->getPosition().x + c->crect.x ,c->getActor()->getPosition().y + c->crect.y,c->crect.width,c->crect.height};

			if (checkRectangle(r1, r2)){
				list.push_back(new Collision(c->getActor(), c));
			}
		}
	}
	return list;
}

std::vector<Collision*> Collider::checkTrigger()
{
	std::vector<Collision*> list = {};
	for (Collider* c : collList)
	{
		if (c != this && c->canPassThrough) {
			Rectangle r1 = { owner.getPosition().x + crect.x ,owner.getPosition().y + crect.y,crect.width,crect.height };
			Rectangle r2 = { c->getActor()->getPosition().x + c->crect.x ,c->getActor()->getPosition().y + c->crect.y,c->crect.width,c->crect.height };
			if (checkRectangle(r1, r2)) {
				Collision* coll = new Collision(c->getActor(), c);
				list.push_back(coll);
				owner.OnTrigger(coll);
				c->getActor()->OnTrigger(new Collision(&owner, this));

			}
		}
	}
	return list;
}

bool Collider::checkRectangle(Rectangle r1, Rectangle r2) {
	if (r1.x + r1.width >= r2.x &&    // r1 right edge past r2 left
		r1.x <= r2.x + r2.width &&    // r1 left edge past r2 right
		r1.y + r1.height >= r2.y &&    // r1 top edge past r2 bottom
		r1.y <= r2.y + r2.height) {    // r1 bottom edge past r2 top
		return true;
	}
	return false;
}




