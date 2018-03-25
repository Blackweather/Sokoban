#pragma once
#include "Item.h"
class Ground : public Item {
public:
	Ground(int x, int y);
	bool Collide(Directions dir) override;
	char* getPath() override;
private:
	char* IMAGE_PATH = "./img/Ground.bmp";
};