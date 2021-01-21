#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>
using namespace std;

int main(int argc, char** argv) {
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	glm::vec2 velocity = glm::vec2(2.0, -1.0);

	SDL_Init(SDL_INIT_EVERYTHING);
	
	cout << "Yay! Dependencies are working correctly!" << endl;

	return 0;
}