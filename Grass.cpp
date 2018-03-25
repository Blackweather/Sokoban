#include "Grass.h"

Grass::Grass(int x, int y) : Item(x,y) {
	type = 'G';
}

char * Grass::getPath()
{
	return IMAGE_PATH;
}

bool Grass::Collide(Directions dir) {
	//player can't be adjacent to grass either way
	return true;
}