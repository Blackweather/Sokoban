#include "Item.h"

Item::Item(int x, int y) : xPosition(x), yPosition(y) {
	isOnEndPoint = false;
}

Item::~Item() {
	SDL_FreeSurface(sprite);
}

void Item::loadSprite(char* path) {
	sprite = SDL_LoadBMP(path);
	if (sprite == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", path, SDL_GetError());
		SDL_Quit();
	}
	SDL_SetColorKey(sprite, SDL_TRUE, 0x000000);
}

SDL_Surface* Item::getSprite() {
	return sprite;
}

bool Item::getIsOnEndPoint() {
	return isOnEndPoint;
}

void Item::setIsOnEndPoint(const bool value) {
	isOnEndPoint = value;
}

int Item::getXPosition() {
	return xPosition;
}

int Item::getYPosition() {
	return yPosition;
}

char Item::getType() {
	return type;
}