#include "Ground.h"

Ground::Ground(int x, int y) : Item(x,y) {
	type = 'E';
}

char * Ground::getPath()
{
	return IMAGE_PATH;
}

bool Ground::Collide(Directions dir) {
	//player can move through tiles
	return true;
}