#include "Game.h"
#include "InputHandler.h"

Game::Game()
{
	currentMapID = 1;
}

Game::~Game()
{
}

void Game::allocMap() {
	gameMap_ = new Map(currentMapID, this);
}

void Game::createMap() {
	allocMap();
}

bool Game::initialize() {
	printf("Program started\n");
	if (!initSDL()) {
		return false;
		printf("Cannot initialize SDL\n");
	}
	if (!loadTextures()) {
		printf("Cannot load textures\n");
		return false;
	}
	mapColors();
	initTime();
	createMap();
	victory = false;
	return true;
}

bool Game::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return false;
	}
	if (!initRenderer()) {
		printf("Cannot initialize renderer\n");
		return false;
	}

	return true;
}

bool Game::initRenderer() {
	// tryb pe³noekranowy / fullscreen mode
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);

	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return false;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Sokoban");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	//disable mouse cursor in window
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

SDL_Surface* Game::loadBMP(char* path) {
	return SDL_LoadBMP(path);
}

bool Game::loadSurface(SDL_Surface** surface, char* path) {
	*surface = loadBMP(path);
	if (surface == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", path, SDL_GetError());
		cleanSDL();
		SDL_Quit();
		return false;
	}
	return true;
}

bool Game::loadTextures() {
	if (!loadSurface(&charset, "./cs8x8.bmp")) {
		printf("Cannot load charset\n");
		return false;
	}

	//black - transparent (just for charset)
	SDL_SetColorKey(charset, SDL_TRUE, 0x000000);

	return true;
}

void Game::mapColors() {
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	coolBlue = SDL_MapRGB(screen->format, 0x6F, 0xA8, 0xFF);
}

void Game::initTime() {
	t1 = SDL_GetTicks();

	quit = false;

	worldTime = 0;
}

void Game::drawMenu() {
	//info text
	//rectangular background
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 30, red, blue);
	//first line of text
	sprintf(text, "Sokoban, elapsed time = %.1lf s", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	//second line of text
	sprintf(text, "ESC - exit, N - New Game, P - next level");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 20, text, charset);
}

void Game::drawVictoryMenu() {
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 30, red, blue);
	sprintf(text, "Congratulations, you solved the puzzle!");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	sprintf(text, "Time = %.1lf s, P - next level", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 20, text, charset);
}



// cleans all SDL Related things
void Game::freeSpace() {
	SDL_FreeSurface(charset);
	cleanSDL();
	SDL_Quit();
}

// renders everything on screen
void Game::render() {
	//updates everything on texture
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);

	//connects the new texture with renderer
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);

	//renders
	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	InputHandler* handler = new InputHandler();
	switch (handler->handleKeyStates()) {
	case MOVE_UP:
		gameMap_->getPlayer()->movePlayer(0, -1);
		break;
	case MOVE_DOWN:
		gameMap_->getPlayer()->movePlayer(0, 1);
		break;
	case MOVE_LEFT:
		gameMap_->getPlayer()->movePlayer(-1, 0);
		break;
	case MOVE_RIGHT:
		gameMap_->getPlayer()->movePlayer(1, 0);
		break;
	case NEW_GAME:
		initTime();
		//call a function reverting the current field
		delete gameMap_;
		createMap();
		break;
	case QUIT:
		quit = true;
		break;
	case NEXT_MAP:
		delete gameMap_;
		initTime();
		currentMapID++;
		if (currentMapID > MAP_COUNT) {
			currentMapID = 1;
		}
		createMap();
		SDL_FillRect(screen, NULL, coolBlue);
		drawMenu();
		gameMap_->drawMap();
		render();
	case NO_EVENT:
		break;
	}

	if (handler->handleQuit() == QUIT) {
		quit = true;
	}

	delete handler;
}

void Game::update() {

	t2 = SDL_GetTicks();

	// here t2-t1 is the time in miliseconds since
	// the last screen was drawn
	// delta is the same time in seconds
	if (!victory) {
		delta = (t2 - t1)*0.001;
		// clear time difference
		t1 = t2;

		//increase world time
		worldTime += delta;

	}
	// fill the screen with nice blue
	SDL_FillRect(screen, NULL, coolBlue);
	//info text
	victory = (gameMap_->getCratesOnPosition() == gameMap_->getNumberOfCrates());
	if (victory) {
		drawVictoryMenu();
	}
	else
		drawMenu();
	gameMap_->drawMap();
	//render everything on screen
	render();

	handleEvents();

}

void Game::gameLoop() {
	while (!quit) {

		//move to update
		update();
	}
}

// frees all key SDL structures
void Game::cleanSDL() {
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::setQuit(const bool value) {
	quit = value;
}

Map* Game::getMap() {
	return gameMap_;
}

SDL_Surface* Game::getScreen() {
	return screen;
}