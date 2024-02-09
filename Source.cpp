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

double Map::getX() { return x; }
double Map::getY() { return y; }
class Player;
Player::Player()
{
	player_texture.loadFromFile("player.jpg");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);

	x = rand() % (900 - 100 + 1) + 100;
	y = rand() % (900 - 100 + 1) + 100;

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

bool Player::CheckWall()
{
	if ((x + 50 >= 1000) || (x <= 0)) return 0;
	if ((y + 50 >= 1000) || (y <= 0)) return 0;
	return 1;
}

Player::Player(const Player& player) 
{
	this->x = player.x;
	this->y = player.y;
	this->health = player.health;
	this->damage = player.damage;
}

double Player::getX() { return x; }

double Player::getY() { return y; }

int Player::getHealth() { return health; }

int Player::getDamage() { return damage; }

void Player::setXY(double x, double y)
{
	this->x = x;
	this->y = y;
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
	for (int i = 0; i < 15; i++) 
	{
		int rnd = rand() % 2;
		if (rnd == 0) buffs[i] = new Damage();
		else buffs[i] = new Health();
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

	Gui sword("sword.png", 0, 900);
	TextGui swordnumb(player->getDamage(), 40, 100, 900);
	Gui health("heart.png", 150, 900);
	TextGui healthnumb(player->getHealth(), 40, 250, 900);

	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		clock.restart();
		swapPlayerType();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				window.close();
			}	
			player->movement(event,deltaTime);
		}
		if (!player->CheckWall()) window.close();
		for (int i = 0; i < 4; i++)
		{
			window.draw(maps[i].rect);
		}
		for (int i = 0; i < 15; i++)
		{
			buffs[i]->draw(window);
		}
		player->checkPosition();
		player->draw(window);
		sword.draw(window);
		swordnumb.draw(window);
		health.draw(window);
		healthnumb.draw(window);
		window.display();
		deltaTime = clock.getElapsedTime();

	}
	timer.EndTime();
	this->TimeInSec = timer.GetTime();

}

void Game::StartTimeCycle()
{
	int w = 500, h = 200;
	sf::Event event; sf::Font font;
	std::string Mess = "Your time is ";
	std::string StTime;

	TimeWindow.create(sf::VideoMode(w, h), "Time");

	StTime = std::to_string(TimeInSec);
	Mess += StTime;
	Mess += " sec.";

	TextGui text(Mess, 40, w / 2 - 150, h / 2 - 40);
	Gui BackGround("BackGroundTime.png", 0, 0);

	while (TimeWindow.isOpen())
	{
		while (TimeWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				TimeWindow.close();
			}
		}
		BackGround.draw(TimeWindow);
		text.draw(TimeWindow);
		TimeWindow.display();
	}
}
class Buff;
class Health;
class Damage;

Buff::Buff() 
{
	x = rand() % 1000;
	y = rand() % 1000;
}

void Buff::draw(sf::RenderWindow& window)
{
	window.draw(buff_sprite);
}

Damage::Damage() 
{
	buff_texture.loadFromFile("buff1.jpg");
	buff_texture.setSmooth(true);
	buff_sprite.setTexture(buff_texture);
	buff_sprite.setPosition(sf::Vector2f(x, y));
}

Health::Health()
{
	buff_texture.loadFromFile("buff2.jpg");
	buff_texture.setSmooth(true);
	buff_sprite.setTexture(buff_texture);
	buff_sprite.setPosition(sf::Vector2f(x, y));
	buff_sprite.setScale(sf::Vector2f(0.05f, 0.05f));
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

int Game::checkCurrId() 
{
	int id;
	for (int i = 0; i < 4; i++) 
	{
		if (player->getX() < maps[i].getX() + 500 && player->getX() > maps[i].getX() && player->getY() < maps[i].getY() + 500 && player->getY() > maps[i].getY()) 
		{
			id = maps[i].getId();
		}
	}
	return id;
}

void Game::swapPlayerType()
{
	double cx = player->getX(), cy = player->getY();
	int id = checkCurrId();
	if (currentId != id)
	{
		currentId = id;
		switch (currentId)
		{
		case 1: {player = new PlayerUsual(); player->setXY(cx, cy); }break;
		case 2: {player = new PlayerSnake(); player->setXY(cx, cy); }break;
		case 3: {player = new PlayerBoss(); player->setXY(cx, cy); }break;
		case 4: {player = new PlayerInvisible(); player->setXY(cx, cy); }break;
		default:
			break;
		}
	}
}

Gui::Gui(std::string filename, int x, int y)
{
	Texture.loadFromFile(filename);
	Sprite.setTexture(Texture);
	Sprite.setPosition(x, y);
}

void Gui::draw(sf::RenderWindow& window)
{
	window.draw(Sprite);
}

TextGui::TextGui(std::string message, int size, int x, int y)
{
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString(message);
	text.setCharacterSize(size);
	text.setPosition(x, y);
	text.setFillColor(sf::Color::Red);
}

TextGui::TextGui(int message, int size, int x, int y)
{
	std::string mess = std::to_string(message);
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString(mess);
	text.setCharacterSize(size);
	text.setPosition(x, y);
	text.setFillColor(sf::Color::White);
}

void TextGui::draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextGui::setstring(int message)
{
	std::string mess = std::to_string(message);
	text.setString(mess);
}

void TextGui::setstring(std::string message)
{
	text.setString(message);
}