#pragma once
#include "Item.h"
class EndPoint : public Item
{
public:
	EndPoint(int x, int y);
	bool Collide(Directions dir) override;
	char* getPath() override;
private:
	char* IMAGE_PATH = "./img/EndPoint.bmp";
};

