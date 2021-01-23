#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>
#include "Constants.h"
#include  "Game.h"
using namespace std;

int main(int argc, char** argv) {
	/*Game* game = new Game();  // I don't want to use the heap
	delete game;*/

	Game game;	//don't put a () here, create game on the stack

	game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game.getIsRunning()) {
		game.ProcessInput();
		game.Update();
		game.Render();
	}

	sol::state lua;
	lua.open_libraries(sol::lib::base);
	glm::vec2 velocity = glm::vec2(2.0, -1.0);
	SDL_Init(SDL_INIT_EVERYTHING);
	cout << "Yay! Dependencies are working correctly!" << endl;

	game.Destroy();

	return 0;
}