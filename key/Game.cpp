#include "Game.h"

void Game::showLogo(){
}

bool Game::chooseMode() { 
	return true; 
}

void Game::start() {
	init();
	if (chooseMode()) {
		load();
		if (run())
			start();
	}
}
