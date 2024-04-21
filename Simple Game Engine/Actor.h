#pragma once
#include <vector>
#include <memory>
#include <set>
#include "Vector2.h"
#include <SDL_stdinc.h>

using std::vector;

class Game;
class Component;
class Collision;

class Actor
{
public:

	enum class ActorState
	{
		Active, Paused, Dead
	};

	enum class Tag
	{
		Wall, Pickup, Player, None
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	void processInput(const struct InputState& inputState);
	virtual void actorInput(const struct InputState& inputState);

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector2 getPosition() const { return position; }
	const Vector2 getScale() const { return scale; }
	const float getRotation() const { return rotation; }
	const Vector2 getForward() const;

	void setPosition(Vector2 positionP);
	void setScale(Vector2 scaleP);
	void setScale(float scaleP);
	void setRotation(float rotation);
	void setState(ActorState as) { state = as; };

	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

	void OnTrigger(Collision* coll);

	Tag getTag() { return actorTag; };

	template <typename CompType>
	inline CompType getComponent()
	{
		for (Component* currComp : components)
		{
			CompType currentEntry = dynamic_cast<CompType>(currComp);
			if (currentEntry != nullptr)
			{
				return currentEntry;
			}
		}
		return nullptr;
	}

private:
	Game& game;
	ActorState state;
	Vector2 position;
	Vector2 scale;
	float rotation;  // Rotation in radians.
	Tag actorTag;

	vector<Component*> components;
};


