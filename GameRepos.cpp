#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Engine.h"
using namespace sf;

int main()
{
	srand(time(NULL));
	Game game;
	game.MainMenu();
	//game.StartGameCycle();
	//game.StartTimeCycle(); //закоментите если время заебало после каждого закрытия
	return 0;
}
