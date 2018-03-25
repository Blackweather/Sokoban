#pragma once
#include "Item.h"
#include "Crate.h"
#include "EndPoint.h"
#include "Grass.h"
#include "Wall.h"
#include "Player.h"
#include "Ground.h"

#include "Directions.h"

class Game;

struct Coords {
	int x;
	int y;
};

class Map {
public:
	Map(int ID, Game* game_);
	~Map();
	Coords itemToMapCoords(int itemX, int itemY);
	void drawMap();
	// doesn't put any items inside
	void allocateItemMap();
	int getIDSize();
	char* getMapPath();
	bool loadMap();
	void drawPlayer();

	Player* getPlayer();
	Item* getItem(int x, int y);
	int getMapHeight();
	int getMapWidth();
	int getID();

	void moveCrate(Item* crate, Directions dir);

	int getNumberOfCrates();
	int getCratesOnPosition();

private:
	// used for switching through maps
	int mapID;

	const int SPRITE_SIZE = 32;

	// map sizes
	int mapWidth = 0, mapHeight = 0;

	// number of crates on map
	// (also endpoints)
	int numberOfCrates = 0;
	// crates on correct position
	int cratesOnPosition = 0;

	Item*** itemMap;
	Player* player;
	Game* selfGame_;
};
