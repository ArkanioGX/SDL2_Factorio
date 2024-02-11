#pragma once
#include "Component.h"
#include "Rectangle.h"
#include <vector>

class Collision;

enum Layer { Walls = 1, Ground = 2 };

class Collider : public Component
{
private :
	bool canPassThrough = false;

	Rectangle crect ;

	static std::vector<Collider*> collList;

public:
	
	Collider(Actor* ownerP,Rectangle r , bool CPT);
	~Collider();
	Collider() = delete;
	Collider(const Collider&) = delete;
	Collider& operator=(const Collider&) = delete;

	std::vector<Collider*> getCollList() { return collList; };

	void addCollider(Collider* c) { collList.push_back(c); }
	void removeCollider(Collider* c) { collList.erase(std::remove(collList.begin(), collList.end(), c), collList.end()); }

	std::vector<Collision*> checkCollision();
	std::vector<Collision*> checkTrigger();
	bool checkRectangle(Rectangle r1, Rectangle r2);

	Actor* getActor() { return &owner; };

	bool getCanPassThrough() { return canPassThrough; }


};

