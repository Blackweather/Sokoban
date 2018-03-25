#pragma once
#include "SDLSample.h"
#include "Directions.h"
#define WALKING_FRAMES 44 // number of animation clips

class Game;

class Player {
public:
	Player(int x, int y, Game* game_);
	~Player();
	bool canMove(Directions dir);
	void movePlayer(int x, int y);
	void animate(Directions dir);
	void loadTexture();
	void setupClips();
	void switchClip(Directions dir, bool isStanding);
	void draw(int mapWidth, int mapHeight);

private:
	//coords corresponding to item array coords
	int xTab, yTab;
	int deltaX = 0, deltaY = 0;
	const int PLAYER_SIZE = 32;
	const int PLAYER_SPEED = 2;
	SDL_Surface* sprite;
	SDL_Rect playerClips[WALKING_FRAMES];
	SDL_Rect currentClip;
	const char* path = "./img/player.bmp";

	Game* selfGame_;
};

