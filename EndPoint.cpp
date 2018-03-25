#include "EndPoint.h"

EndPoint::EndPoint(int x, int y) : Item(x, y) {
	type = 'F';
}

char * EndPoint::getPath()
{
	return IMAGE_PATH;
}

bool EndPoint::Collide(Directions dir) {
	//player can move onto endpoint floor
	return true;
}