#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "TilemapSpriteComponent.h"
#include "BackgroundSpriteComponent.h"
#include <iostream>
#include <algorithm>

bool Game::initialize() {
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowHeight = window.getHeight();
	int windowWidth = window.getWidth();

	return isWindowInit && isRendererInit;
}

void Game::loop() {
	Timer timer;
	float dt = 0;
	while (isRunning) {
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::close() {
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}

	isUpdatingActors = true;
	for (auto actor:actors){
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::update(float dt) {
	//Update Actors
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->update(dt);
	}
	isUpdatingActors = false;

	for (auto pendingActor : pendingActors) {
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	//Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::ActorState::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::render() {
	renderer.beginDraw();

	renderer.draw();

	renderer.endDraw();
}

void Game::addActor(Actor* actor) {
	if (isUpdatingActors) {
		pendingActors.emplace_back(actor);
	}
	else {
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor) {
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors)) {
		std::iter_swap(iter, end(pendingActors) - 1); 
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors)) {
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::load() {
	Assets::loadTexture(renderer,"Res/Ship.png","Ship");
	Assets::loadTexture(renderer, "Res/TerrainSimplifiedTileset.png", "TerrainTileset");

	Actor* ship = new Actor();
	SpriteComponent* sc = new SpriteComponent(ship, Assets::getTexture("Ship"));
	ship->addComponent(sc);
	ship->setPosition(Vector2(100, 100));

	//test Tilemap
	Actor* tmActor= new Actor();
	tmActor->setScale(5);
	Tileset* tset = new Tileset(Assets::getTexture("TerrainTileset"), 16, 1);
	Tilemap* tmap = new Tilemap(tset);
	TilemapSpriteComponent* tmsc = new TilemapSpriteComponent(tmActor, tmap);

	
}

void Game::unload() {

	while (!actors.empty()) {
		delete actors.back();
	}

	Assets::clear();
}