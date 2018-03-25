#include "Map.h"
#include <string.h>
#include <cstdio>
#include "Game.h"

using namespace std;

Map::Map(int ID, Game* game)
{
	selfGame_ = game;

	mapID = ID;
	loadMap();
}

Map::~Map()
{
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			delete itemMap[i][j];
		}
		delete itemMap[i];
	}
	delete itemMap;
	delete player;
}

Coords Map::itemToMapCoords(int itemX, int itemY) {
	int x = itemX;
	x *= SPRITE_SIZE;
	x += SPRITE_SIZE / 2;
	// shift to center of screen
	int dx = (SCREEN_WIDTH - (mapWidth*SPRITE_SIZE)) / 2;
	x += dx;

	int y = itemY;
	y *= SPRITE_SIZE;
	y += SPRITE_SIZE / 2;
	const int MENU_HEIGHT = 40;
	int dy = (SCREEN_HEIGHT - (mapHeight*SPRITE_SIZE)) / 2;
	dy += MENU_HEIGHT / 2;
	y += dy;

	Coords toReturn;
	toReturn.x = x;
	toReturn.y = y;
	return toReturn;

}

void Map::drawMap() {
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			Coords itemCoords = itemToMapCoords(j, i);
			DrawSurface(selfGame_->getScreen(), itemMap[i][j]->getSprite(), itemCoords.x, itemCoords.y);
		}
	}
	player->draw(mapWidth, mapHeight);
}

void Map::allocateItemMap() {
	itemMap = new Item**[mapHeight];
	for (int i = 0; i < mapHeight; i++) {
		itemMap[i] = new Item*[mapWidth];
	}
}

int Map::getIDSize() {
	int sizeReturned = 0;
	int ID = mapID;
	while (ID != 0) {
		ID /= 10;
		sizeReturned++;
	}
	return sizeReturned;
}

char* Map::getMapPath() {
	char firstPart[] = "./maps/map";
	const int MID_POSITION = 10;
	const int CHARS_TO_ALLOC = 15;
	int ID = mapID;
	//allocate the path char array
	int currentIDSize = getIDSize();
	char* path = new char[CHARS_TO_ALLOC + currentIDSize];
	strcpy(path, firstPart);
	//copy ID numbers to path
	for (int i = currentIDSize - 1; i >= 0; i--) {
		char number = (ID % 10) + '0';
		ID /= 10;
		path[MID_POSITION + i] = number;
	}
	path[MID_POSITION + currentIDSize] = '.';
	path[MID_POSITION + currentIDSize + 1] = 't';
	path[MID_POSITION + currentIDSize + 2] = 'x';
	path[MID_POSITION + currentIDSize + 3] = 't';
	path[MID_POSITION + currentIDSize + 4] = '\0';

	return path;
}

bool Map::loadMap() {
	char* path = getMapPath();

	FILE* mapToLoad;
	mapToLoad = fopen(path, "rb");
	if (mapToLoad == NULL) {
		printf("CANNOT LOAD MAP");
		return false;
	}

	fscanf(mapToLoad, "%d\n", &mapHeight);
	fscanf(mapToLoad, "%d\n", &mapWidth);

	//allocate map
	allocateItemMap();

	//convert corresponding chars to objects
	//fill itemMap
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			switch (getc(mapToLoad)) {
			case 'B':
				itemMap[i][j] = new Crate(i, j, this);
				numberOfCrates++;
				itemMap[i][j]->loadSprite(itemMap[i][j]->getPath());
				break;
			case 'G':
				itemMap[i][j] = new Grass(i, j);
				itemMap[i][j]->loadSprite(itemMap[i][j]->getPath());
				break;
			case 'E':
				itemMap[i][j] = new Ground(i, j);
				itemMap[i][j]->loadSprite(itemMap[i][j]->getPath());
				break;
			case 'W':
				itemMap[i][j] = new Wall(i, j);
				itemMap[i][j]->loadSprite(itemMap[i][j]->getPath());
				break;
			case 'F':
				itemMap[i][j] = new EndPoint(i, j);
				itemMap[i][j]->loadSprite(itemMap[i][j]->getPath());
				break;
			case 'P':
				itemMap[i][j] = new Ground(i, j);
				itemMap[i][j]->loadSprite(itemMap[i][j]->getPath());
				//spawn player here
				player = new Player(j, i, selfGame_);
				player->loadTexture();
				break;
			default:
				break;
			}
		}
		fscanf(mapToLoad, "\n");
	}
}

// cause the player is kinda drawn other way than other blocks
void Map::drawPlayer() {
	player->draw(mapWidth, mapHeight);
}

Player* Map::getPlayer() {
	return player;
}

Item* Map::getItem(int x, int y) {
	return itemMap[y][x];
}

int Map::getMapHeight() {
	return mapHeight;
}

int Map::getMapWidth() {
	return mapWidth;
}

int Map::getID() {
	return mapID;
}

void Map::moveCrate(Item* crate, Directions dir) {


	int x = crate->getYPosition();
	int y = crate->getXPosition();
	int tmpX = x;
	int tmpY = y;

	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	}

	// item on next field
	Item* check = itemMap[y][x];

	//stored for later usage
	bool isOnEndPoint = crate->getIsOnEndPoint();
	bool willBeEndPoint = false;

	// is next field endpoint
	char type = check->getType();
	if (type == 'F') {
		willBeEndPoint = true;
		//check->setIsOnEndPoint(true);
		cratesOnPosition++;
	}
	else {
		//check->setIsOnEndPoint(false);
	}

	//put crate on next field
	delete check;
	check = new Crate(y, x, this);
	if (willBeEndPoint) {
		check->setIsOnEndPoint(true);
	}
	itemMap[y][x] = check;
	itemMap[y][x]->loadSprite(itemMap[y][x]->getPath());

	if (isOnEndPoint) {
		//1. if crate is on endpoint
		//put endpoint on crate's coords
		delete crate;
		itemMap[tmpY][tmpX] = new EndPoint(tmpY, tmpX);
		itemMap[tmpY][tmpX]->loadSprite(itemMap[tmpY][tmpX]->getPath());
		cratesOnPosition--;
		//decrease cratesOnPosition from Map.h
	}
	else {
		//2. if crate is not on endpoint
		//put ground on crate's coords
		delete crate;
		itemMap[tmpY][tmpX] = new Ground(tmpY, tmpX);
		itemMap[tmpY][tmpX]->loadSprite(itemMap[tmpY][tmpX]->getPath());
	}

	//redraw?
	selfGame_->drawMenu();
	selfGame_->getMap()->drawMap();
	selfGame_->render();

	//check for endgame
	if (cratesOnPosition == numberOfCrates) {
		selfGame_->drawVictoryMenu();
		selfGame_->render();
	}

}

int Map::getCratesOnPosition() {
	return cratesOnPosition;
}

int Map::getNumberOfCrates() {
	return numberOfCrates;
}