#include "Wall.h"

Wall::Wall(int x, int y) : Item(x,y) {
	type = 'W';
}

char * Wall::getPath()
{
	return IMAGE_PATH;
}

bool Wall::Collide(Directions dir) {
	// player can't move into wall
	return false;
}