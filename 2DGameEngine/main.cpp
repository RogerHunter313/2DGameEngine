#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>
#include "Constants.h"
#include  "Game.h"
using namespace std;

int main(int argc, char** argv) {
	Game* game = new Game();

	game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->getIsRunning()) {
		game->processInput();
		//game->update();
		game->render();
	}

	game->destroy();

	return 0;
}