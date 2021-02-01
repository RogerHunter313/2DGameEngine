#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

class Collision {
public:
	static bool CheckRectangleCollision(const SDL_Rect& rectangleA, SDL_Rect& rectangleB);  //AABB axis aligned bounding box

};

#endif