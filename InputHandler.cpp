#include "InputHandler.h"

InputHandler::InputHandler() {
}

InputHandler::~InputHandler() {

}

Event InputHandler::handleKeyStates() {
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		return MOVE_UP;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		return MOVE_DOWN;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		return MOVE_LEFT;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		return MOVE_RIGHT;
	}
	else if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
		return QUIT;
	}
	else if (currentKeyStates[SDL_SCANCODE_N]) {
		return NEW_GAME;
	}
	else return handleNextMap();
}

Event InputHandler::handleNextMap() {
	// poll event because it reads key just when its pressed
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_p) {
				return NEXT_MAP;
			}
			break;
		default:
			return NO_EVENT;
		}
	}
	return NO_EVENT;
}

Event InputHandler::handleQuit() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return QUIT;
			break;
		default:
			return NO_EVENT;
		}
	}
	return NO_EVENT;
}