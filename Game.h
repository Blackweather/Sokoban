#pragma once
#include "Map.h"
#include "SDLSample.h"

enum Event {
	QUIT,
	NO_EVENT,
	MOVE_UP,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	NEW_GAME,
	NEXT_MAP
};

//class containing all game methods and info
class Game {
public:
	Game();
	~Game();
	//initializes the interface
	bool initialize();
	//initializes SDL and graphics parameters
	bool initSDL();
	bool initRenderer();

	SDL_Surface* loadBMP(char* path);
	bool loadSurface(SDL_Surface** surface, char* path);
	bool loadTextures();
	void mapColors();
	void initTime();

	void freeSpace();
	void update();
	void render();
	void handleEvents();

	void cleanSDL();

	void drawMenu();
	void drawVictoryMenu();

	//whole game loop
	void gameLoop();

	void setQuit(const bool value);

	//creates the map on screen and in memory
	void createMap();
	void allocMap();
	Map* getMap();

	SDL_Surface* getScreen();

private:
	const int MAP_COUNT = 14;
	int currentMapID;

	//used for window and renderer setup
	int rc;

	// t1 - starting time, t2 - current time (all in miliseconds)
	int t1, t2;

	// delta - t2-t1 in seconds
	// worldTime - time since program started (seconds)
	double delta, worldTime;

	bool victory = false;

	//used for quitting the game
	bool quit;
	
	//used for handling colours
	int black, green, red, blue;
	int coolBlue;

	//used for storing text used in menu
	char text[128];

	SDL_Surface *screen, *charset;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Map* gameMap_;

};
