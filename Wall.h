#pragma once
#include "Item.h"

class Wall : public Item
{
public:
	Wall(int x, int y);
	bool Collide(Directions dir) override;
	char* getPath() override;
private:
	char* IMAGE_PATH = "./img/Wall.bmp";
};