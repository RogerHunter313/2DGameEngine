#include "Game.h"
#include "Constants.h"

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 1.0f;
float projectileVelY = 1.0f;

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
	projectilePosX += projectileVelX;
	projectilePosY += projectileVelY;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21,255);
	SDL_RenderClear(renderer);

	SDL_Rect projectile{
		(int)projectilePosX,
		(int)projectilePosY,
		10,
		10
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &projectile);

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

