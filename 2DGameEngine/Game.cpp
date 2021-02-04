#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <glm/glm.hpp>
#include "EntityManager.h"
#include "AssetManager.h"
#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "Map.h"
#include "ColliderComponent.h"
#include "TextLabelComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* tileMap;

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {

}

bool Game::getIsRunning() const {
	return this->isRunning;
}

void Game::Initialize(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "Error initializing SDL." << endl;
		return;	
	}
	if (TTF_Init() != 0) {
		std::cerr << "Error initializing SDL TTF" << std::endl;
		return;
	}

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		cerr << "Error creating SDL window." << endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		cerr << "Error creating SDL renderer." << endl;
		return;
	}

	LoadLevel(0);

	isRunning = true;
	return;
}

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));  //modified chopperEntity to be global and renamed to player so it can control the game camera

void Game::LoadLevel(int levelNumber) {
	// Start including new assets to the assetManager list
	std::string textureFilePath = "./assets/images/tank-big-right.png";  //just pasted his assets folder where my .cpp files were stored
	assetManager->AddTexture("tank-image", textureFilePath.c_str());  //c_str gets "old school" pointer to char string
	std::string textureFilePath2 = "./assets/images/tank-small-right.png";
	// assets below are added in just one line
	assetManager->AddTexture("small-tank-image", std::string("./assets/images/tank-small-right.png").c_str()); //same as above just with one line
	assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
	assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
	assetManager->AddTexture("jungle-tile-image", std::string("./assets/tilemaps/jungle.png").c_str());
	assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
	assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

	tileMap = new Map("jungle-tile-image", 2, 32);  // name, scale, tilesize
	tileMap->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

	// Start including entities and also component to them
	Entity& bigTankEntity(manager.AddEntity("big-tank", ENEMIES_LAYER));
	bigTankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	bigTankEntity.AddComponent<SpriteComponent>("tank-image");
	bigTankEntity.AddComponent<ColliderComponent>("enemy", 0, 0, 32, 32);

	// creating second entity
	Entity& smallTankEntity(manager.AddEntity("small-tank", ENEMIES_LAYER));  
	smallTankEntity.AddComponent<TransformComponent>(50, 50, 30, 30, 32, 32, 1);
	smallTankEntity.AddComponent<SpriteComponent>("small-tank-image");

	
	player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);  
	player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
	player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

	Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

	Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
	heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
	heliport.AddComponent<SpriteComponent>("heliport-image");
	heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

	Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
	labelLevelName.AddComponent<TextLabelComponent>(10, 10, "First Level...", "charriot-font", WHITE_COLOR);

	manager.ListAllEntities();
}

void Game::ProcessInput() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
		}
		default: {
			break;
		}
	}
}

void Game::Update() {
	//Sleep the execution until we reach the target frame time in milliseconds
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	//Only call delay if we are too far to prcocess this frame
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}
	
	// Wait until 16ms has elapssed since the last frame	
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME)) {  BAD, don't do
	//	//just pause or waste time until we reach	FRAME_TARGET_TIME.  WAIT while loops are bad because 100% of the cpu core will go to the while loop.  we don't want to waste resources
	//}

	//deltaTime is the difference in ticks from the last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;  //dividing by 1000 to know how much should you move by second, SDL_GetTicks apparently returns miliseconds

	//Clamp deltaTime to a maximum value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;  //if delta time is greater that 0.05f, just set it to 0.05s

	//sets the new ticks/timestamps for the ccurrent frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks();   //SDL_GetTicks starts keeping time from the point we call SDL_INIT_EVERYTHING
	
	manager.Update(deltaTime);

	HandleCameraMovement();
	CheckCollisions();
}

void Game::Render() {
	// set the background color
	SDL_SetRenderDrawColor(renderer, 21, 21, 21,255);
	
	// clear the back buffer
	SDL_RenderClear(renderer);

	if (manager.HasNoEntities()) {
		return;
	}

	manager.Render();

	//SDL_RenderCopy(renderer, NULL, NULL, &projectile);
	//SDL2 does all double buffering, which means, nothing shows up on the screen 
	//until everything is rendered and the SDL_RenderPresent executes below

	SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
	TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

	camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);  // pixel can be added here to adjust position of player
	camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT/ 2);

	//clamping values of the camera
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

//void Game::CheckCollisions() {
//	std::string collisionTagType = manager.CheckEntityCollisions(player);
//	if (collisionTagType.compare("enemy") == 0) {
//		// TODO: do something when collision is identified with an enemy
//		isRunning = false;
//	}
//}

void Game::CheckCollisions() {
	CollisionType collisionType = manager.CheckCollisions();
	if (collisionType == PLAYER_ENEMY_COLLISION) {
		//ProcessGameOver();
		std::cout << "huh?" << endl;
		isRunning = false;
	}
	if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
		//ProcessNextLevel(1);
		std::cout << "Bruhh..." << endl;
	}
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	//TODO delete all the new pointers for components, entities, entityManager where applicable
}

