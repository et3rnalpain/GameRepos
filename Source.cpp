#include "Engine.h"


class Map;
Map::Map()
{
	id = 0;
	x = y = -1;
	color = color.Black;
}
int Map::getId()
{
	return id;
}
void Map::setId(int id)
{
	this->id = id;
	switch (id)
	{
	case 1:
	{
		color = color.Red;
	}break;
	case 2:
	{
		color = color.Yellow;
	}break;
	case 3:
	{
		color = color.Blue;
	}break;
	case 4:
	{
		color = color.Green;
	}break;
	}
}
void Map::setXY(int x_, int y_)
{
	x = x_;
	y = y_;
	Map::rect.setSize(sf::Vector2f(h, w));
	Map::rect.setPosition(sf::Vector2f(x, y));
	Map::rect.setFillColor(color);
}
class Player;
Player::Player() {};
void Player::attack()
{
	//huy
};


//ZALUOPA


void Player::move()
{
	//huy nikita
};
void Player::checkPosition()
{
	//HUI 
	//HUIIII!!
};
class PlayerUsual;
void PlayerUsual::move()
{
	x += ms;
	y += ms;
}
class PlayerInvisible;
class PlayerBoss;
class PlayerSnake;
class Game;
void Game::StartGameCycle()
{
	window.create(sf::VideoMode(1000, 1000), "Game");
	int array[4] = { 1,2,3,4 };
	std::random_shuffle(&array[0], &array[3]);
	for (int i = 0; i < 4; i++)
	{
		maps[i].setId(array[i]);
	}
	maps[0].setXY(0, 0);
	maps[1].setXY(500, 0);
	maps[2].setXY(0, 500);
	maps[3].setXY(500, 500);
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(maps[i].rect);
		}
		window.display();
	}
}