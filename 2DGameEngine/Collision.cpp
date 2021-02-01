#include "Collision.h"

bool Collision::CheckRectangleCollision(const SDL_Rect& rectangleA, SDL_Rect& rectangleB) {
	return {
		rectangleA.x + rectangleA.w >= rectangleB.x &&
		rectangleB.x + rectangleB.w >= rectangleA.x &&		// in cas size variance is large
		rectangleA.y + rectangleA.h >= rectangleB.y &&
		rectangleB.y + rectangleB.h >= rectangleA.y		//accounting for size variance
	};
}