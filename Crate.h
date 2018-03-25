#pragma once
#include "Item.h"

class Map;

class Crate : public Item {
public:
	Crate(int x, int y, Map* map);
	bool Collide(Directions dir) override;
	char* getPath() override;
private:
	char* IMAGE_PATH = "./img/Crate.bmp";
	Map* selfMap_;
};

