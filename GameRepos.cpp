#include <iostream>
#include "Engine.h"
using namespace sf;

int main()
{
	srand(time(NULL));
	Game game;
	game.MainMenu();
	game.StartGameCycle();
	game.StartTimeCycle();
	return 0;
}
