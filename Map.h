#pragma once
#include "Engine.h"

class Map //класс карты
{
private:
	int id;
	double x, y, h = (SCREEN_HEIGHT / 2), w = (SCREEN_WIDTH / 2);
	sf::Color color;

public:
	Gui fon;
	sf::RectangleShape rect;
	Map();
	int getId(); //получить айди поля (1-4)
	double getX();
	double getY();
	void setId(int id);
	void setXY(int x_, int y_);
};