#include "Player.h"
#include "Game.h"

Player::Player(int x, int y, Game* game_) : xTab(x), yTab(y), selfGame_(game_) {

}

Player::~Player() {
	SDL_FreeSurface(sprite);
}

bool Player::canMove(Directions dir) {
	int x = xTab;
	int y = yTab;
	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	if (x >= 0 && x < selfGame_->getMap()->getMapWidth()
		&& y >= 0 && y < selfGame_->getMap()->getMapHeight()) {
		Item* check = selfGame_->getMap()->getItem(x, y);
		char type = check->getType();
		bool willWork = check->Collide(dir);
		if (type == 'B') {
			//check if is crate
			if (willWork) {
				//move crate
				selfGame_->getMap()->moveCrate(check, dir);
			}
			return willWork;
		}
		return willWork;
	}
	else {
		return false;
	}
	return true;
}

void Player::movePlayer(int x, int y) {
	//gets direction based on x,y
	Directions dir = (x == 1) ? RIGHT :
		((x == -1) ? LEFT :
		((y == 1) ? DOWN :
			UP));
	//starting clip
	switchClip(dir, true);

	//number of times it moves
	for (int i = 0; i < PLAYER_SIZE / PLAYER_SPEED; i++) {

		if (canMove(dir)) {
			switch (dir) {
			case UP:
				deltaY -= PLAYER_SPEED;
				break;
			case DOWN:
				deltaY += PLAYER_SPEED;
				break;
			case LEFT:
				deltaX -= PLAYER_SPEED;
				break;
			case RIGHT:
				deltaX += PLAYER_SPEED;
				break;
			default:
				break;
			}
			switchClip(dir, false);
			SDL_Delay(10);
		}

		selfGame_->drawMenu();
		selfGame_->getMap()->drawMap();
		selfGame_->render();
		if (deltaX == PLAYER_SIZE) {
			deltaX = 0;
			xTab++;
		}
		else if (deltaX == -PLAYER_SIZE) {
			deltaX = 0;
			xTab--;
		}

		if (deltaY == PLAYER_SIZE) {
			deltaY = 0;
			yTab++;
		}
		else if (deltaY == -PLAYER_SIZE) {
			deltaY = 0;
			yTab--;
		}

	}
	// final clip
	switchClip(dir, true);
}

void Player::loadTexture() {
	sprite = SDL_LoadBMP(path);
	if (sprite == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", path, SDL_GetError());
		SDL_Quit();
	}
	else {
		SDL_SetColorKey(sprite, SDL_TRUE, 0x000000);
		setupClips();
	}
}

void Player::setupClips() {
	//down stand [0]
	//left stand [11]
	//up stand [22]
	//right stand [33]
	//each direction has 10 walking clips

	for (int i = 0; i < 44; i++) {
		playerClips[i].x = i % 11;
		playerClips[i].x *= PLAYER_SIZE;
		playerClips[i].x++;

		playerClips[i].y = i / 11;
		playerClips[i].y *= PLAYER_SIZE;

		playerClips[i].w = PLAYER_SIZE;
		playerClips[i].h = PLAYER_SIZE;
	}
	currentClip = playerClips[0];
}

void Player::switchClip(Directions dir, bool isStanding) {
	if (isStanding) {
		switch (dir) {
		case UP:
			currentClip = playerClips[22];
			break;
		case DOWN:
			currentClip = playerClips[0];
			break;
		case LEFT:
			currentClip = playerClips[11];
			break;
		case RIGHT:
			currentClip = playerClips[33];
			break;
		}
	}
	else {
		//rotate through clips

		//first we get current clip number
		int clipNumber;
		for (int i = 0; i < WALKING_FRAMES; i++) {
			if (currentClip.x == playerClips[i].x&&currentClip.y == playerClips[i].y) {
				clipNumber = i;
				break;
			}
		}

		switch (dir) {
		case UP:
			//next frame
			clipNumber++;
			//is it in bounds
			clipNumber = (clipNumber > 32) ? clipNumber - 33 + 22 : clipNumber;
			break;
		case DOWN:
			clipNumber++;
			clipNumber = (clipNumber > 10) ? clipNumber - 11 : clipNumber;
			break;
		case LEFT:
			clipNumber++;
			clipNumber = (clipNumber > 21) ? clipNumber - 22 + 11 : clipNumber;
			break;
		case RIGHT:
			clipNumber++;
			clipNumber = (clipNumber > 43) ? clipNumber - 44 + 33 : clipNumber;
			break;
		}
		currentClip = playerClips[clipNumber];
	}
}

void Player::draw(int mapWidth, int mapHeight) {
	int x = xTab;
	int y = yTab;
	x *= PLAYER_SIZE;
	x += PLAYER_SIZE / 2;
	// shift to center of screen
	int dx = (SCREEN_WIDTH - (mapWidth*PLAYER_SIZE)) / 2;
	x += dx;

	y *= PLAYER_SIZE;
	y += PLAYER_SIZE / 2;
	const int MENU_HEIGHT = 40;
	int dy = (SCREEN_HEIGHT - (mapHeight*PLAYER_SIZE)) / 2;
	dy += MENU_HEIGHT / 2;
	y += dy;

	SDL_Rect dest;
	dest.x = x - PLAYER_SIZE / 2 + deltaX;
	dest.y = y - PLAYER_SIZE / 2 + deltaY;
	dest.w = PLAYER_SIZE;
	dest.h = PLAYER_SIZE;
	SDL_BlitSurface(sprite, &currentClip, selfGame_->getScreen(), &dest);
}