#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
using namespace std;

class Game {
	
	public:
		Game();
		~Game();
		int ticksLastFrame = 0;
		bool getIsRunning() const;
		static SDL_Renderer* renderer;  //https://www.geeksforgeeks.org/static-keyword-cpp/
		void LoadLevel(int levelNumber);
		void Initialize(int width, int height);
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();	

	private:
		bool isRunning;
		SDL_Window* window;
		

};

#endif
