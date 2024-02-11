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
	acceleration = 2;
	deceleration = 0.94;
	health = 10;
	damage = 10;

	invis = false;
};

Player::Player(double x, double y, double health, double damage)
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
	acceleration = 2;
	deceleration = 0.94;
	this->health = health;
	this->damage = damage;

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

void Player::attack(Bullet* bullet, double dir_x, double dir_y, double player_x, double player_y) {};

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

void Player::playerTookDamage(){
	this->health--;
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

int Player::getDirection()
{
	if (this->movement_vector.x == 0 && this->movement_vector.y < 0)
		return 1;
	else if (this->movement_vector.x == 0 && this->movement_vector.y > 0)
		return 2;
	else if (this->movement_vector.x > 0 && this->movement_vector.y == 0)
		return 3;
	else if (this->movement_vector.x < 0 && this->movement_vector.y == 0)
		return 4;
	else return 1;
}

void Player::setDirection(int dir) {};

/* Наследники класса Игрок */

class PlayerUsual; //Обычный

class PlayerInvisible; //Невидимый
void PlayerInvisible::draw(sf::RenderWindow& window) {};

class PlayerBoss; //В зоне с боссом
void PlayerBoss::attack(Bullet* bullet, double dir_x, double dir_y, double player_x, double player_y)
{
	if (!bullet->isBulletAlive()) {
		bullet = new Bullet(dir_x, dir_y, player_x, player_y);
	}
}

class PlayerSnake; //Движется змейкой
void PlayerSnake::movement(double dir_x, double dir_y)
{
	if (dir_x == 0.f && dir_y == -1.f)
		this->dir = 1;
	else if (dir_x == 0.f && dir_y == 1.f)
		this->dir = 2;
	else if (dir_x == 1.f && dir_y == 0.f)
		this->dir = 3;
	else if (dir_x == -1.f && dir_y == 0.f)
		this->dir = 4;
}
void PlayerSnake::checkPosition()
{
	this->x += this->snake_move_x[this->dir - 1];
	this->y += this->snake_move_y[this->dir - 1];
	this->player_sprite.setPosition(sf::Vector2f(x, y));
}

void PlayerSnake::setDirection(int dir) {
	this->dir = dir;
}

/* Пуля */

class Bullet;
Bullet::Bullet()
{
	bullet_texture.loadFromFile("pulya.jpg");
	bullet_texture.setSmooth(true);
	bullet_sprite.setTexture(bullet_texture);

	this->x = 0;
	this->y = 0;
	this->bullet_vector.x = 0;
	this->bullet_vector.y = 0;
	bullet_sprite.setPosition(this->x, this->y);
	this->max_speed = 500;
	this->min_speed = 1;
	this->acceleration = 1.6;
	
	isAlive = false;
}

Bullet::Bullet(double dir_x, double dir_y, double player_x, double player_y)
{
	bullet_texture.loadFromFile("pulya.jpg");
	bullet_texture.setSmooth(true);
	bullet_sprite.setTexture(bullet_texture);

	this->x = player_x;
	this->y = player_y;
	this->bullet_vector.x = dir_x;
	this->bullet_vector.y = dir_y;
	bullet_sprite.setPosition(this->x, this->y);
	this->max_speed = 500;
	this->min_speed = 1;
	this->acceleration = 1.6;
	
	isAlive = true;
}

void Bullet::movement()
{
	if (isAlive) {
		this->bullet_vector.x *= this->acceleration;
		this->bullet_vector.y *= this->acceleration;

		this->x += this->bullet_vector.x;
		this->y += this->bullet_vector.y;
	}
}

void Bullet::checkPosition()
{
	if (std::abs(this->bullet_vector.x) > this->max_speed)
		isAlive = false;
	if (std::abs(this->bullet_vector.y) > this->max_speed)
		isAlive = false;
	bullet_sprite.setPosition(x, y);
}

void Bullet::draw(sf::RenderWindow& window)
{
	if (isAlive)
		window.draw(bullet_sprite);
}

bool Bullet::isBulletAlive()
{
	return this->isAlive;
}

double Bullet::getX() {
	return this->x;
}

double Bullet::getY() {
	return this->y;
}

/* Моб */

class Mob;
Mob::Mob()
{
	mob_texture.loadFromFile("mob.jpg");
	mob_texture.setSmooth(true);
	mob_sprite.setTexture(mob_texture);

	this->health = 1000;
	this->damage = 9;
	this->acceleration = 1.2;

	x = rand() % ((SCREEN_WIDTH - 100) - 100 + 1) + 100;
	y = rand() % ((SCREEN_WIDTH - 100) - 100 + 1) + 100;

	movement_vector.x = rand() % ((-1) - 1 - 1) + 1;
	movement_vector.y = rand() % ((-1) - 1 - 1) + 1;
	alive = true;
	
	mob_sprite.setPosition(x, y);
}

Mob::Mob(double x, double y)
{
	mob_texture.loadFromFile("mob.jpg");
	mob_texture.setSmooth(true);
	mob_sprite.setTexture(mob_texture);

	this->health = 10;
	this->damage = 9;
	this->acceleration = 1.2;

	this->x = x;
	this->y = y;

	movement_vector.x = rand() % ((-1) - 1 - 1) + 1;
	movement_vector.y = rand() % ((-1) - 1 - 1) + 1;
	alive = true;

	mob_sprite.setPosition(x, y);
}

void Mob::setXY(double x, double y)
{
	this->x = x;
	this->y = y;
	mob_sprite.setPosition(x, y);
}

double Mob::getX() {
	return this->x;
}

double Mob::getY() {
	return this->y;
}

void Mob::draw(sf::RenderWindow& window){
	window.draw(mob_sprite);
}

bool Mob::checkWall()
{
	if (x + (mob_sprite.getTextureRect().width / 2) >= SCREEN_WIDTH || x + (mob_sprite.getTextureRect().width / 2) <= 0) return 0;
	if (y + (mob_sprite.getTextureRect().height / 2) >= SCREEN_HEIGHT || y + (mob_sprite.getTextureRect().height / 2) <= 0) return 0;
	return 1;
}

void Mob::movement()
{
	if (!checkWall()) {
		movement_vector.x *= (-1);
		movement_vector.y *= (-1);
	}
	x += movement_vector.x;
	y += movement_vector.y;

	mob_sprite.setPosition(x, y);

	acceleration = rand() % ((-5) - 5 + 1) - 1;
}

void Mob::updateCondition(Player* p, Bullet* b)
{
	this->movement();
	if (p->getX() >= this->getX() && p->getX() <= this->getX() + mob_sprite.getTextureRect().width
		&& p->getY() >= this->getY() && p->getY() <= this->getY() + mob_sprite.getTextureRect().height){
		p->playerTookDamage();
	}
	if (b->getX() >= this->getX() && b->getX() <= this->getX() + mob_sprite.getTextureRect().width
		&& b->getY() >= this->getY() && b->getY() <= this->getY() + mob_sprite.getTextureRect().height)
		std::cout << "BULLET HIT";
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
	regenerateBuff();
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
	//TextGui swordnumb(player->getDamage(), 40, 100, 900);
	Gui health("heart.png", 150, 900);
	//TextGui healthnumb(player->getHealth(), 40, 250, 900);

	sf::Vector2f move_dir = sf::Vector2f(0.f, 0.f);
	sf::Vector2f tmp_dir = sf::Vector2f(0.f, -1.f);

	/*Music fon("fon.wav", 50, 1);
	fon.play();*/

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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				move_dir.x = 0.6f; move_dir.y = -0.6; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				move_dir.x = -0.6f; move_dir.y = -0.6; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				move_dir.x = 0.6f; move_dir.y = 0.6; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				move_dir.x = -0.6f; move_dir.y = 0.6; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				move_dir.x = 0; move_dir.y = -1; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				move_dir.x = 0; move_dir.y = 1; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				move_dir.x = 1; move_dir.y = 0; tmp_dir = move_dir;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				move_dir.x = -1; move_dir.y = 0; tmp_dir = move_dir;
			}
			else {
				move_dir.x = 0; move_dir.y = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->checkCurrId() == 1) {
				/*player->attack(bullet, tmp_dir.x, tmp_dir.y, player->getSpriteCenter().x, player->getSpriteCenter().y);*/
				if (!bullet->isBulletAlive()) {
					bullet = new Bullet(tmp_dir.x, tmp_dir.y, player->getSpriteCenter().x, player->getSpriteCenter().y);
				}
			}
		}
		
		TextGui swordnumb(player->getDamage(), 40, 100, 900);
		TextGui healthnumb(player->getHealth(), 40, 250, 900);

		player->movement(move_dir.x, move_dir.y);
		player->checkPosition();
		//std::cout << this->checkCurrId();
		bullet->movement();
		bullet->checkPosition();
		mob->updateCondition(player, bullet);
		if (!player->CheckWall()) window.close();
		for (int i = 0; i < 4; i++)
		{
			window.draw(maps[i].rect);
		}
		for (int i = 0; i < 15; i++)
		{
			buffs[i]->draw(window);
		}
		sword.draw(window);
		swordnumb.draw(window);
		health.draw(window);
		healthnumb.draw(window);
		bullet->draw(window);
		player->draw(window);
		mob->draw(window);
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
		if (player->getSpriteCenter().x <= maps[i].getX() + SCREEN_WIDTH / 2 && player->getSpriteCenter().x >= maps[i].getX() && player->getSpriteCenter().y <= maps[i].getY() + SCREEN_HEIGHT / 2 && player->getSpriteCenter().y >= maps[i].getY())
		{
			id = maps[i].getId();
		}
	}
	//std::cout << player->getSpriteCenter().x << " " << player->getSpriteCenter().y << std::endl;
	return id;
}

void Game::swapPlayerType()
{
	double cx = player->getX(), cy = player->getY();
	int tmp_hp = player->getHealth(), tmp_dmg = player->getDamage();
	int id = checkCurrId();
	int dir = player->getDirection();
	if (currentId != id)
	{
		currentId = id;
		switch (currentId)
		{
		case 1: {delete player; player = new PlayerUsual(cx, cy, tmp_hp, tmp_dmg); }break;
		case 2: {delete player; player = new PlayerSnake(cx, cy, tmp_hp, tmp_dmg); player->setDirection(dir); }break;
		case 3: {delete player; player = new PlayerBoss(cx, cy, tmp_hp, tmp_dmg); }break;
		case 4: {delete player; player = new PlayerInvisible(cx, cy, tmp_hp, tmp_dmg); }break;
		default:
			break;
		}
	}
}

bool Game::isBuffsInCollision(Buff* buff1, Buff* buff2) 
{
	return (buff1->getX() >= buff2->getX() && buff1->getX() <= (buff2->getX() + 50) && buff1->getY() >= buff2->getY() && buff1->getY() <= (buff2->getY() + 50));
}

void Game::regenerateBuff() 
{
	for (int i = 0; i < 15; i++) 
	{
		for (int z = 0; z < 15; z++) 
		{
			if (i != z) 
			{
				if (isBuffsInCollision(buffs[i], buffs[z]))
				{
					double 	x = rand() % 900 + 50, y = rand() % 900 + 50;
					buffs[i]->setPosition(x, y);
					i = 0;
					z = 0;
				}
			}
		}
	}
}

/* Бонусы */

class Buff;
class Health;
class Damage;

Buff::Buff() 
{
	x = rand() % 900 + 50;
	y = rand() % 900 + 50;
}

void Buff::draw(sf::RenderWindow& window)
{
	window.draw(buff_sprite);
}

void Buff::setPosition(double x, double y) 
{
	this->x = x;
	this->y = y;
	buff_sprite.setPosition(x, y);
}

double Buff::getX() { return x; }
double Buff::getY() { return y; }

Damage::Damage() 
{
	buff_texture.loadFromFile("buff1.png");
	buff_texture.setSmooth(true);
	buff_sprite.setTexture(buff_texture);
	buff_sprite.setPosition(sf::Vector2f(x, y));
}

Health::Health()
{
	buff_texture.loadFromFile("buff2.png");
	buff_texture.setSmooth(true);
	buff_sprite.setTexture(buff_texture);
	buff_sprite.setPosition(sf::Vector2f(x, y));
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

Sound::Sound(std::string namefile, int volume)
{
	buffer.loadFromFile(namefile);
	sound.setBuffer(buffer);
	sound.setVolume(volume);
}

void Sound::ChangeVolume(int volume)
{
	sound.setVolume(volume);
}

void Sound::play()
{
	sound.play();
}

Music::Music(std::string namefile, int volume, bool loop)
{
	music.openFromFile(namefile);
	music.setVolume(volume);
	music.setLoop(loop); //1 передавайте если надо зациклить МУЗЯКУ
}

void Music::ChangeVolume(int volume)
{
	music.setVolume(volume);
}

void Music::play()
{
	music.play();
}