#pragma once
#include "Item.h"

class Grass : public Item
{
public:
	Grass(int x, int y);
	bool Collide(Directions dir) override;
	char* getPath() override;
private:
	char* IMAGE_PATH = "./img/Grass.bmp";
};