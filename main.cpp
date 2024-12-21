#include <iostream>
#include "Game.h"
#include <chrono>
#include <thread>
using namespace std;

int main() {
	srand(static_cast<unsigned>(time(NULL)));
	Game game;

	while (game.isWindowOpen()) {
		// Render
		game.render();

		// Update
		game.update();
	}

	return 0;
}