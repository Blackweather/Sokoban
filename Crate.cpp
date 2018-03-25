#include "Crate.h"
#include "Map.h"

Crate::Crate(int x, int y, Map* map) : Item(x, y), selfMap_(map) {
	type = 'B';
}

char* Crate::getPath() {
	return IMAGE_PATH;
}

bool Crate::Collide(Directions dir) {
	//return true if crate can be moved to next position
	int tmpX = yPosition;
	int tmpY = xPosition;
	//direction to where crate is pushed
	switch (dir) {
	case UP:
		tmpY--;
		break;
	case DOWN:
		tmpY++;
		break;
	case LEFT:
		tmpX--;
		break;
	case RIGHT:
		tmpX++;
		break;
	}

	int mapWidth = selfMap_->getMapWidth();
	int mapHeight = selfMap_->getMapHeight();

	if (tmpX<0 || tmpX>mapWidth || tmpY<0 || tmpY>mapHeight) {
		return false;
	}

	Item* itemOnPosition;
	itemOnPosition = selfMap_->getItem(tmpX, tmpY);

	char type = itemOnPosition->getType();

	//item is ground
	if (type == 'E') {
		return true;
	}

	//item is endpoint
	if (type == 'F') {
		return true;
	}

	//cant move into boxes for now
	return false;
}