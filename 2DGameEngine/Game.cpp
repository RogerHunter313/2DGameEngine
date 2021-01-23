#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <glm/glm.hpp>

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(100.0f, 100.0f);

Game::Game() {
	this->isRunning = false;
}

Game::~Game() {

}

bool Game::getIsRunning() const {
	return this->isRunning;
}

void Game::initialize(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << "Error initializing SDL." << endl;
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

	isRunning = true;
	return;
}

void Game::processInput() {
	SDL_Event event;
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

void Game::update() {
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

	// Use deltaTime to update my game objects
	projectilePos = glm::vec2(
		projectilePos.x + projectileVel.x * deltaTime,
		projectilePos.y + projectileVel.y * deltaTime
	);
}

void Game::render() {
	// set the background color
	SDL_SetRenderDrawColor(renderer, 21, 21, 21,255);
	
	// clear the back buffer
	SDL_RenderClear(renderer);

	// draw alal the game objects

	SDL_Rect projectile = {
		(int) projectilePos.x,
		(int) projectilePos.y,
		10,
		10
	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &projectile);

	//SDL_RenderCopy(renderer, NULL, NULL, &projectile);
	//SDL2 does all double buffering, which means, nothing shows up on the screen 
	//until everything is rendered and the SDL_RenderPresent executes below

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

