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
#include "Camera.h"
#include "CameraControllerComponent.h"
#include "TilePlacerComponent.h"
#include "ConveyorTile.h"
#include "MachineTileComponent.h"
#include "MinerTile.h"
#include "InventoryTile.h"
#include <rapidjson/document.h>
#include "TilePlacerRenderComponent.h"

bool Game::initialize() {
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowHeight = window.getHeight();
	int windowWidth = window.getWidth();
	bool isInputInit = inputSystem.initialize();

	return isWindowInit && isRendererInit && isInputInit;
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
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		isRunning = inputSystem.processEvent(event);
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	// Escape: quit game
	if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
	{
		isRunning = false;
	}

	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(input);
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
	Assets::loadTexture(renderer, "Res/MachineTileset.png", "MachineTileset");
	Assets::loadTexture(renderer, "Res/MachineTileset.png", "MachineTilesetAlpha");
	//Assets::loadTexture(renderer, "Res/TS_Dungeon1.png", "TerrainTileset");
	
	Assets::loadTexture(renderer, "Res/TestTileset.png", "TestTileset");
	Assets::loadTexture(renderer, "Res/Iron.png", "Iron");
	Assets::loadTexture(renderer, "Res/Silver.png", "Silver");

	
	//Camera
	Actor* camActor = new Actor();
	Camera* camera = new Camera(camActor,Vector2(700,500),0.5);
	CameraControllerComponent* CCC = new CameraControllerComponent(camActor);

	//Load Tileset
	Tileset* worldTset = new Tileset(Assets::getTexture("TerrainTileset"), 16);
	Tileset* machineTset = new Tileset(Assets::getTexture("MachineTileset"), 16);


	//main Tilemap
	
	Actor* worldTM= new Actor();
	
	Tilemap* tmap = new Tilemap(worldTM, worldTset,false);
	
	TilemapSpriteComponent* tmsc = new TilemapSpriteComponent(worldTM, tmap);
	{
		Vector2 min = Vector2::zero;
		Vector2 max = Vector2::zero;

		//Get the tilemap limit
		tmap->getLimit(min, max);

		//Set the clamp to the camera
		CCC->setLimit(min, max);
	}

	//Machine Tilemap Setup
	Actor* machineTM = new Actor();
	Tilemap* tmap2 = new Tilemap(machineTM, machineTset,true);
	TilemapSpriteComponent* tmsc2 = new TilemapSpriteComponent(machineTM, tmap2);
	
	TilePlacerComponent* tpc2 = new TilePlacerComponent(machineTM, tmap2, std::vector<Tile*>{
		new ConveyorTile(ConveyorTile::base), //Conveyor lv 1
		new ConveyorTile(ConveyorTile::upgrade), //Conveyor lv 2
		new MinerTile(MinerTile::baseSMiner), //Miner Tile (Silver Variant)
		new MinerTile(MinerTile::baseIMiner), //Miner Tile (Iron Variant)
		new InventoryTile(InventoryTile::baseInventory) //Tile Storage (unused)
	});
	TilePlacerRenderComponent* tprc = new TilePlacerRenderComponent(machineTM, tmap2, tpc2);
	MachineTileComponent* mtc = new MachineTileComponent(machineTM,tmap2);
}

void Game::unload() {

	while (!actors.empty()) {
		delete actors.back();
	}

	Assets::clear();
}