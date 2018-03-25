#pragma once
#include "SDLSample.h"
#include "Directions.h"

class Item
{
public:
	Item(int x, int y);
	~Item();
	//tmp =0 to make it possible for subclasses
	void loadSprite(char* path);
	virtual char* getPath() = 0;
	SDL_Surface* getSprite();
	virtual bool Collide(Directions dir) = 0;
	bool getIsOnEndPoint();
	void setIsOnEndPoint(const bool value);
	int getXPosition();
	int getYPosition();
	char getType();

protected:
	int xPosition, yPosition;
	bool isOnEndPoint;
	char type;
private:
	SDL_Surface* sprite;
	char* IMAGE_PATH;
};