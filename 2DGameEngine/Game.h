#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"
#include <iostream>
using namespace std;

class AssetManager;

class Game {
	
	public:
		Game();
		~Game();
		int ticksLastFrame = 0;
		bool getIsRunning() const;
		static SDL_Renderer* renderer;  //https://www.geeksforgeeks.org/static-keyword-cpp/
		static AssetManager* assetManager;
		static SDL_Event event;
		static SDL_Rect camera;
		void LoadLevel(int levelNumber);
		void Initialize(int width, int height);
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();	
		void HandleCameraMovement();

	private:
		bool isRunning;
		SDL_Window* window;
		

};

#endif
