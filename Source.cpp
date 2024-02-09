#include "Engine.h"

/* Карта */

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

/* Игрок */

class Player;
Player::Player()
{
	player_texture.loadFromFile("player.jpg");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);

	x = rand() % ((SCREEN_WIDTH - 100) - 100 + 1) + 100;
	y = rand() % ((SCREEN_WIDTH - 100) - 100 + 1) + 100;
	movement_vector.x = 0;
	movement_vector.y = 0;
	player_sprite.setPosition(x,y);
	max_speed = 6;
	min_speed = 1;
	acceleration = 3;
	deceleration = 0.98;
	health = 10;
	damage = 10;

	invis = false;
};

Player::Player(double x, double y) 
{
	player_texture.loadFromFile("player.jpg");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);

	this->x = x;
	this->y = y;
	movement_vector.x = 0;
	movement_vector.y = 0;
	player_sprite.setPosition(x,y);
	max_speed = 6;
	min_speed = 1;
	acceleration = 3;
	deceleration = 0.98;
	health = 10;
	damage = 10;

	invis = false;

	invis = false;
}

Player::Player(const Player& player)
{
	player_texture.loadFromFile("player.jpg");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);

	this->x = player.x;
	this->y = player.y;
	this->movement_vector = player.movement_vector;
	player_sprite.setPosition(this->x, this->y);
	this->max_speed = player.max_speed;
	this->min_speed = player.min_speed;
	this->acceleration = player.acceleration;
	this->deceleration = player.deceleration;
	this->health = player.health;
	this->damage = player.damage;

	this->invis = player.invis;
}

void Player::attack()
{

};

void Player::movement(double direction_x, double direction_y)
{
	this->movement_vector.x += direction_x * this->acceleration;
	this->movement_vector.y += direction_y * this->acceleration;

	if (std::abs(this->movement_vector.x) > this->max_speed)
		this->movement_vector.x = this->max_speed * ((this->movement_vector.x < 0.f) ? -1.f : 1.f);
	if (std::abs(this->movement_vector.y) > this->max_speed)
		this->movement_vector.y = this->max_speed * ((this->movement_vector.y < 0.f) ? -1.f : 1.f);

	this->x += this->movement_vector.x;
	this->y += this->movement_vector.y;
}

void Player::checkPosition()
{
	this->movement_vector.x *= this->deceleration;
	this->movement_vector.y *= this->deceleration;

	if (std::abs(this->movement_vector.x) < this->min_speed)
		this->movement_vector.x = 0;
	if (std::abs(this->movement_vector.y) < this->min_speed)
		this->movement_vector.y = 0;
	player_sprite.setPosition(x, y);
};

void Player::draw(sf::RenderWindow& window){
	window.draw(player_sprite);
}

bool Player::CheckWall()
{
	if (this->getSpriteCenter().x >= SCREEN_WIDTH || this->getSpriteCenter().x <= 0) return 0;
	if (this->getSpriteCenter().y >= SCREEN_HEIGHT || this->getSpriteCenter().y <= 0) return 0;
	return 1;
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

sf::Vector2f Player::getSpriteCenter()
{
	sf::Vector2f center(this->x + (player_sprite.getTextureRect().width / 2), this->y + (player_sprite.getTextureRect().height / 2));
	return center;
}

/* Наследники класса Игрок */

class PlayerUsual; //Обычный

class PlayerInvisible; //Невидимый

class PlayerBoss; //В зоне с боссом

class PlayerSnake; //Движется змейкой
void PlayerSnake::movement(double dir_x, double dir_y)
{
	if (dir_x == 0.f && dir_y == -1.f)
		this->direction = 1;
	else if (dir_x == 0.f && dir_y == 1.f)
		this->direction = 2;
	else if (dir_x == 1.f && dir_y == 0.f)
		this->direction = 3;
	else if (dir_x == -1.f && dir_y == 0.f)
		this->direction = 4;
}
void PlayerSnake::checkPosition()
{
	this->x += this->snake_move_x[this->direction - 1];
	this->y += this->snake_move_y[this->direction - 1];
	this->player_sprite.setPosition(sf::Vector2f(x, y));
}

/* Игра */

class Game;
void Game::StartGameCycle()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	window.setFramerateLimit(144);
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
	maps[1].setXY(SCREEN_WIDTH / 2, 0);
	maps[2].setXY(0, SCREEN_HEIGHT / 2);
	maps[3].setXY(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	sf::Event event;
	sf::Clock clock;
	sf::Time deltaTime;

	Timer timer;
	timer.StartTime();

	Gui sword("sword.png", 0, 900);
	TextGui swordnumb(player->getDamage(), 40, 100, 900);
	Gui health("heart.png", 150, 900);
	TextGui healthnumb(player->getHealth(), 40, 250, 900);

	sf::Vector2f move_dir = sf::Vector2f(0.f, 0.f);

	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		clock.restart();
		swapPlayerType();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				move_dir.x = 0; move_dir.y = -1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				move_dir.x = 0; move_dir.y = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				move_dir.x = 1; move_dir.y = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				move_dir.x = -1; move_dir.y = 0;
			}
			else {
				move_dir.x = 0; move_dir.y = 0;
			}
		}
		player->movement(move_dir.x, move_dir.y);
		player->checkPosition();
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

int Game::checkCurrId()
{
	int id = 0;
	for (int i = 0; i < 4; i++)
	{
		if (player->getX() <= maps[i].getX() + 500 && player->getX() >= maps[i].getX() && player->getY() <= maps[i].getY() + 500 && player->getY() >= maps[i].getY())
		{
			id = maps[i].getId();
		}
	}
	std::cout << player->getX() << " " << player->getY() << std::endl;
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
		case 1: {delete player; player = new PlayerUsual(cx, cy); }break;
		case 2: {delete player; player = new PlayerSnake(cx, cy); }break;
		case 3: {delete player; player = new PlayerBoss(cx, cy); }break;
		case 4: {delete player; player = new PlayerInvisible(cx, cy);  }break;
		default:
			break;
		}
	}
}

/* Бонусы */

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
	buff_texture.loadFromFile("buff1.png");
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

/* Таймер */

class Timer;
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

/* Спрайты */

class Gui;
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