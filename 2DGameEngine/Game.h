#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
using namespace std;

class Game {
	
	public:
		Game();
		~Game();
		bool getIsRunning() const;
		void initialize(int width, int height);
		void processInput();
		void update();
		void render();
		void destroy();	

	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;

};

#endif
