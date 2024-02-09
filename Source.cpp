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
Player::Player()
{
	player_shape.setSize(sf::Vector2f(50, 50));
	player_texture.loadFromFile("player.jpg");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);

	x = rand() % 1000;
	y = rand() % 1000;

	movement_speed = 10;
	health = 10;
	damage = 10;

	invis = false;
};

void Player::attack()
{

};
void Player::movement(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->y -= this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->y += this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->x += this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->x -= this->movement_speed;
	this->player_shape.setPosition(sf::Vector2f(x, y));
	this->player_sprite.setPosition(sf::Vector2f(x, y));
};
void Player::checkPosition()
{

};
void Player::draw(sf::RenderWindow& window){
	window.draw(player_sprite);
}

class PlayerUsual;
void PlayerUsual::movement(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->y -= this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->y += this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->x += this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->x -= this->movement_speed;
	this->player_shape.setPosition(sf::Vector2f(x, y));
	this->player_sprite.setPosition(sf::Vector2f(x, y));
}

class PlayerInvisible;

class PlayerBoss;

class PlayerSnake;
void PlayerSnake::movement(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->direction = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->direction = 2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->direction = 3;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->direction = 4;
}
void PlayerSnake::checkPosition()
{
	this->x += this->snake_move_x[this->direction - 1];
	this->y += this->snake_move_y[this->direction - 1];
	this->player_shape.setPosition(sf::Vector2f(x, y));
	this->player_sprite.setPosition(sf::Vector2f(x, y));
}

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
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
			}	
			player->movement(event);
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(maps[i].rect);
		}
		player->checkPosition();
		player->draw(window);
		window.display();
	}
}