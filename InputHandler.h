#pragma once
#include "Game.h"
class InputHandler {
public:
	InputHandler();
	~InputHandler();
	//handles all key events
	Event handleKeyStates();
	//handles quitting with X
	Event handleQuit();
	//handles going to next map
	Event handleNextMap();

private:
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
};