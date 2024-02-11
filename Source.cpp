#include "Engine.h"

/* ����� */

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
		fon.makeSprite("fokinsky.png");
	}break;
	case 2:
	{
		fon.makeSprite("volodarka.png");
	}break;
	case 3:
	{
		fon.makeSprite("sovok.png");
	}break;
	case 4:
	{
		fon.makeSprite("bezhitsky.png");
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
	fon.setPosition(x, y);
	
}

double Map::getX() { return x; }
double Map::getY() { return y; }

/* ����� */

class Player;
Player::Player()
{
	player_texture.loadFromFile("chel.png");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);
	player_sprite.setOrigin(player_sprite.getTextureRect().width / 2, player_sprite.getTextureRect().height / 2);

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

	damage_taken = false;
};

Player::Player(double x, double y, double health, double damage)
{
	player_texture.loadFromFile("chel.png");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);
	player_sprite.setOrigin(player_sprite.getTextureRect().width / 2, player_sprite.getTextureRect().height / 2);

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

	damage_taken = false;
}

Player::Player(const Player& player)
{
	player_texture.loadFromFile("chel.png");
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);
	player_sprite.setOrigin(player_sprite.getTextureRect().width / 2, player_sprite.getTextureRect().height / 2);

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

	this->damage_taken = player.damage_taken;
}

void Player::attack(Bullet* bullet, double dir_x, double dir_y, double player_x, double player_y) {};

void Player::movement(double direction_x, double direction_y)
{
	if (direction_x == 0.f && direction_y == -1.f) {
		player_sprite.setRotation(180);
	}
	else if (direction_x == 0.f && direction_y == 1.f) {
		player_sprite.setRotation(0);
	}
	else if (direction_x == 1.f && direction_y == 0.f) {
		player_sprite.setRotation(270);
	}
	else if (direction_x == -1.f && direction_y == 0.f) {
		player_sprite.setRotation(90);
	}
	else if (direction_x == -0.6f && direction_y == 0.6f) {
		player_sprite.setRotation(45);
	}
	else if (direction_x == -0.6f && direction_y == -0.6f) {
		player_sprite.setRotation(325);
	}
	else if (direction_x == 0.6f && direction_y == -0.6f) {
		player_sprite.setRotation(225);
	}
	else if (direction_x == 0.6f && direction_y == 0.6f) {
		player_sprite.setRotation(135);
	}

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
	if (this->getX() >= SCREEN_WIDTH || this->getX() <= 0) return 0;
	if (this->getY() >= SCREEN_HEIGHT || this->getY() <= 0) return 0;
	return 1;
}

void Player::tookDamage(Mob* m){
	if (damage_taken == false) {
		this->health -= m->getDamage();
		this->damage_taken = true;
	}

	x += movement_vector.x * (-20);
	y += movement_vector.y * (-20);

	if (movement_vector.x != 0 || movement_vector.y != 0)
		this->damage_taken = false;
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

/*sf::Vector2f Player::getSpriteCenter()
{
	sf::Vector2f center(this->x + (player_sprite.getTextureRect().width / 2), this->y + (player_sprite.getTextureRect().height / 2));
	return center;
}*/

sf::Sprite Player::getSprite(){
	return this->player_sprite;
}

void Player::setSprite(std::string filename){
	player_texture.loadFromFile(filename);
	player_texture.setSmooth(true);
	player_sprite.setTexture(player_texture);
	player_sprite.setOrigin(player_sprite.getTextureRect().width / 2, player_sprite.getTextureRect().height / 2);

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

void Player::setScale(double x, double y){
	this->player_sprite.setScale(x, y);
}

/* ���������� ������ ����� */

class PlayerUsual; //�������

class PlayerInvisible; //���������
void PlayerInvisible::draw(sf::RenderWindow& window) {};

class PlayerBoss; //� ���� � ������
void PlayerBoss::attack(Bullet* bullet, double dir_x, double dir_y, double player_x, double player_y)
{
	if (!bullet->isBulletAlive()) {
		bullet = new Bullet(dir_x, dir_y, player_x, player_y);
	}
}

class PlayerSnake; //�������� �������
void PlayerSnake::movement(double dir_x, double dir_y)
{
	if (dir_x == 0.f && dir_y == -1.f) {
		this->dir = 1; player_sprite.setRotation(270); player_sprite.setScale(1, 1);
	}
	else if (dir_x == 0.f && dir_y == 1.f){
		this->dir = 2; player_sprite.setRotation(90); player_sprite.setScale(1, 1);
	}
	else if (dir_x == 1.f && dir_y == 0.f){
		this->dir = 3; player_sprite.setRotation(0); player_sprite.setScale(1, 1);
	}
	else if (dir_x == -1.f && dir_y == 0.f){
		this->dir = 4; player_sprite.setRotation(0); player_sprite.setScale(-1,1);
	}
}
void PlayerSnake::checkPosition()
{
	this->x += this->snake_move_x[this->dir - 1];
	this->y += this->snake_move_y[this->dir - 1];
	this->player_sprite.setPosition(sf::Vector2f(x, y));
}

void PlayerSnake::setDirection(int dir) {
	this->dir = dir;
	if (this->dir == 1) {
		player_sprite.setRotation(270); 
	}
	else if (this->dir == 2) {
		player_sprite.setRotation(90);
	}
	else if (this->dir = 3) {
		player_sprite.setRotation(0);
	}
	else if (this->dir = 4) {
		player_sprite.setRotation(0);
	}
	this->player_sprite.setScale(0.5, 0.5);
}

/* ���� */

class Bullet;
Bullet::Bullet()
{
	bullet_texture.loadFromFile("pulya.png");
	bullet_texture.setSmooth(true);
	bullet_sprite.setTexture(bullet_texture);
	bullet_sprite.setOrigin(bullet_sprite.getTextureRect().width / 2, bullet_sprite.getTextureRect().height / 2);

	this->x = 0;
	this->y = 0;
	this->bullet_vector.x = 0;
	this->bullet_vector.y = 0;
	bullet_sprite.setPosition(this->x, this->y);
	this->max_speed = 500;
	this->min_speed = 1;
	this->acceleration = 1.3;
	
	isAlive = false;
}

Bullet::Bullet(double dir_x, double dir_y, double player_x, double player_y)
{
	bullet_texture.loadFromFile("pulya.png");
	bullet_texture.setSmooth(true);
	bullet_sprite.setTexture(bullet_texture);
	bullet_sprite.setOrigin(bullet_sprite.getTextureRect().width / 2, bullet_sprite.getTextureRect().height / 2);


	this->x = player_x;
	this->y = player_y;
	this->bullet_vector.x = dir_x;
	this->bullet_vector.y = dir_y;
	bullet_sprite.setPosition(this->x, this->y);
	this->max_speed = 500;
	this->min_speed = 1;
	this->acceleration = 1.3;
	
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

void Bullet::removeBullet() {
	this->isAlive = false; 
	this->x = -100;
	this->y = -100;
	this->bullet_vector.x = -100;
	this->bullet_vector.y = -100;
	this->bullet_sprite.setPosition(x, y);
}

/* ��� */

class Mob;
Mob::Mob()
{

	mob_texture.loadFromFile("mob.jpg");
	mob_texture.setSmooth(true);
	mob_sprite.setTexture(mob_texture);

	this->health = 100;
	this->damage = 9;
	this->acceleration = 1.2;

	x = rand() % ((SCREEN_WIDTH - 100) - 100 + 1) + 100;
	y = rand() % ((SCREEN_WIDTH - 100) - 100 + 1) + 100;
	ix = x; iy = y;
	movement_vector.x = rand() % ((-1) - 1 - 1) + 1;
	movement_vector.y = rand() % ((-1) - 1 - 1) + 1;
	alive = true;
	
	mob_sprite.setPosition(x, y);
}

Mob::Mob(double x, double y)
{
	ix = x; iy = y;
	mob_texture.loadFromFile("mob.jpg");
	mob_texture.setSmooth(true);
	mob_sprite.setTexture(mob_texture);

	this->health = 100;
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

int Mob::getHealth() {
	return this->health;
}

int Mob::getDamage() {
	return this->damage;
}

void Mob::draw(sf::RenderWindow& window){
	window.draw(mob_sprite);
}

int Mob::checkWall()
{
	if (x + (mob_sprite.getTextureRect().width) >= ix+400 || x <= ix-100) return 1;
	if (y + (mob_sprite.getTextureRect().height) >= iy+400 || y <= iy-100) return 2;
	return 0;
}

void Mob::movement()
{
	if (checkWall()==1) {
		movement_vector.x *= (-1);
		
	}
	else if (checkWall() == 2) 
	{
		movement_vector.y *= (-1);
	}

	x += movement_vector.x;
	y += movement_vector.y;

	mob_sprite.setPosition(x, y);

	acceleration = rand() % ((-5) - 5 + 1) - 1;
}

void Mob::updateCondition(Player* p, Bullet* b)
{
	bool dmg_flag = false;
	this->movement();
	if (p->getX() >= this->getX() && p->getX() <= this->getX() + mob_sprite.getTextureRect().width
		&& p->getY() >= this->getY() && p->getY() <= this->getY() + mob_sprite.getTextureRect().height
		&& dmg_flag == false) {
		p->tookDamage(this);
	}
	if (b->getX() >= this->getX() && b->getX() <= this->getX() + mob_sprite.getTextureRect().width
		&& b->getY() >= this->getY() && b->getY() <= this->getY() + mob_sprite.getTextureRect().height){
		this->tookDamage(p); b->removeBullet();
	}
}

void Mob::tookDamage(Player* p){
	this->health -= p->getDamage();
}

/* ���� */

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

	for (int i = 0; i < 4; i++)
	{
		if (maps[i].getId() == 1) mob = new Mob(maps[i].getX() + 100, maps[i].getY() + 100);
	}

	Gui sword("sword.png", 0, 900);
	TextGui swordnumb(player->getDamage(), 40, 100, 900);
	Gui health("heart.png", 150, 900);
	TextGui healthnumb(player->getHealth(), 40, 250, 900);

	TextGui bossDamage(mob->getDamage(), 30, int(mob->getX())+20, int(mob->getY()-40));
	Gui bossDamageSprite("sword.png", mob->getX(), mob->getY()-20);
	bossDamageSprite.resize(0.2, 0.2);
	TextGui bossHealth(mob->getHealth(), 30, int(mob->getX()) + 60, int(mob->getY()-40));
	Gui bossHealthSprite("heart.png", mob->getX()+40, mob->getY()-20);
	bossHealthSprite.resize(0.2, 0.2);

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
				if (!bullet->isBulletAlive()) {
					//bullet = new Bullet(tmp_dir.x, tmp_dir.y, player->getSpriteCenter().x, player->getSpriteCenter().y);
					bullet = new Bullet(tmp_dir.x, tmp_dir.y, player->getX(), player->getY());
				}
			}
		}
		
		swordnumb.setstring(player->getDamage());
		healthnumb.setstring(player->getHealth());

		bossDamage.setPosition(int(mob->getX())+20, int(mob->getY() - 40));
		bossHealth.setPosition(int(mob->getX()) + 60, int(mob->getY() - 40));
		bossDamageSprite.setPosition(mob->getX(), mob->getY() - 20);
		bossHealthSprite.setPosition(mob->getX()+40, mob->getY() - 20);
		bossHealth.setstring(mob->getHealth());

		player->movement(move_dir.x, move_dir.y);
		player->checkPosition();
		//std::cout << this->checkCurrId();
		bullet->movement();
		bullet->checkPosition();
		mob->updateCondition(player, bullet);
		if (!player->CheckWall()) window.close();
		for (int i = 0; i < 4; i++)
		{
			maps[i].fon.draw(window);
		}
		for (int i = 0; i < 15; i++)
		{
			buffs[i]->draw(window);
		}

		bossDamageSprite.draw(window);
		bossHealthSprite.draw(window);
		bossDamage.draw(window);
		bossHealth.draw(window);

		bullet->draw(window);
		player->draw(window);
		mob->draw(window);

		sword.draw(window);
		swordnumb.draw(window);
		health.draw(window);
		healthnumb.draw(window);

		window.display();
		deltaTime = clock.getElapsedTime();
		if (player->getHealth() <= 0) { window.close(); }
		if (mob->getHealth() <= 0) { window.close(); }
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
		if (player->getX() <= maps[i].getX() + SCREEN_WIDTH / 2 && player->getX() >= maps[i].getX() && player->getY() <= maps[i].getY() + SCREEN_HEIGHT / 2 && player->getY() >= maps[i].getY())
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
		case 1: {delete player; player = new PlayerBoss(cx, cy, tmp_hp, tmp_dmg); player->setSprite("chel_with_gun.png"); player->setScale(0.5, 0.5); }break;
		case 2: {delete player; player = new PlayerSnake(cx, cy, tmp_hp, tmp_dmg); player->setSprite("tachka.png"); player->setDirection(dir); player->setScale(1, 1);  }break;
		case 3: {delete player; player = new PlayerUsual(cx, cy, tmp_hp, tmp_dmg); player->setSprite("chel.png"); player->setScale(0.5, 0.5);}break;
		case 4: {delete player; player = new PlayerInvisible(cx, cy, tmp_hp, tmp_dmg); player->setSprite("chel.png"); player->setScale(0.5, 0.5); }break;
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

/* ������ */

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

/* ������ */

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

/* ������� */

class Gui;
Gui::Gui(std::string filename, int x, int y)
{
	Texture.loadFromFile(filename);
	Sprite.setTexture(Texture);
	Sprite.setPosition(x, y);
}

void Gui::makeSprite(std::string filename) 
{
	Texture.loadFromFile(filename);
	Sprite.setTexture(Texture);
};

sf::Sprite Gui::getSprite() { return Sprite; }

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
	music.setLoop(loop); //1 ����������� ���� ���� ��������� ������
}

void Music::ChangeVolume(int volume)
{
	music.setVolume(volume);
}

void Music::play()
{
	music.play();
}