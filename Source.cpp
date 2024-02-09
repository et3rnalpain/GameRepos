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
	player_texture.loadFromFile("player.jpg");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);

	x = rand() % 1000;
	y = rand() % 1000;

	movement_speed = 25;
	health = 10;
	damage = 10;

	invis = false;
};

void Player::attack()
{

};
void Player::movement(sf::Event event, sf::Time deltaTime)
{
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->y -= this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->y += this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->x += this->movement_speed;
	else if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->x -= this->movement_speed;
	this->player_sprite.setPosition(sf::Vector2f(x, y));
};
void Player::checkPosition()
{

};
void Player::draw(sf::RenderWindow& window){
	window.draw(player_sprite);
}

class PlayerUsual;
void PlayerUsual::movement(sf::Event event, sf::Time deltaTime)
{
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->y -= this->movement_speed;
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->y += this->movement_speed;
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->x += this->movement_speed;
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->x -= this->movement_speed;
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->y -= this->movement_speed * cos(45 * M_PI) / 180;
			this->x += this->movement_speed * sin(45 * M_PI) / 180;
	}
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->y += this->movement_speed * cos(45 * M_PI) / 180;
		this->x += this->movement_speed * sin(45 * M_PI) / 180;
	}
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->y += this->movement_speed * cos(45 * M_PI) / 180;
		this->x -= this->movement_speed * sin(45 * M_PI) / 180;
	}
	if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->y -= this->movement_speed * cos(45 * M_PI) / 180;
			this->x -= this->movement_speed * sin(45 * M_PI) / 180;
		}
	this->player_sprite.setPosition(sf::Vector2f(x, y));
}

class PlayerInvisible;

class PlayerBoss;

class PlayerSnake;
void PlayerSnake::movement(sf::Event event, sf::Time deltaTime)
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
	sf::Clock clock;
	sf::Time deltaTime;

	Timer timer;
	timer.StartTime();

	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
			}	
			player->movement(event,deltaTime);
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(maps[i].rect);
		}
		for (int i = 0; i < 10; i++)
		{
			//buffs[i].draw(window);
		}
		player->checkPosition();
		player->draw(window);
		window.display();
		deltaTime = clock.getElapsedTime();

	}

	timer.EndTime();
	std::cout << timer.GetTime();

}
class Buff;
class Health;
class Damage;

Buff::Buff(bool type) 
{
	x = rand() % 1000;
	y = rand() % 1000;
}

void Buff::draw(sf::RenderWindow& window)
{
	window.draw(this->buff_sprite);
}


void Timer::StartTime()
{
	clock.restart();
	seconds = 0;
}

void Timer::EndTime()
{
	seconds = static_cast<unsigned int>(clock.getElapsedTime().asSeconds());
}

int Timer::GetTime()
{
	return seconds;
}
