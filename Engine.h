#pragma once
#include "SFML/Graphics.hpp"
#include "SFML\Audio.hpp"
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

#define M_PI 3.1415926535
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000


class Map //класс карты
{
private:
	int id;
	double x, y, h = (SCREEN_HEIGHT / 2), w = (SCREEN_WIDTH / 2);
	sf::Color color;
public:
	sf::RectangleShape rect;
	Map();
	int getId(); //получить айди поля (1-4)
	double getX();
	double getY();
	void setId(int id);
	void setXY(int x_, int y_);
};

class Bullet
{
private:
	sf::Texture bullet_texture;
	sf::Sprite bullet_sprite;
	sf::Vector2f bullet_vector;
	double x, y, acceleration, max_speed, min_speed;
	bool isAlive;
public:
	Bullet();
	Bullet(double dir_x, double dir_y, double player_x, double player_y);
	void movement();
	void checkPosition();
	void draw(sf::RenderWindow& window);
	bool isBulletAlive();
	double getX();
	double getY();
};

class Player //класс игрока абстрактный
{
protected:
	sf::Texture player_texture;
	sf::Sprite player_sprite;
	sf::Vector2f movement_vector;
	double x, y,acceleration, deceleration, max_speed, min_speed, health, damage;
	bool invis;
public:
	Player();
	Player(double x, double y, double health, double damage);
	Player(const Player& player);

	virtual void attack(Bullet* bullet, double dir_x, double dir_y, double player_x, double player_y);
	virtual void movement(double dir_x, double dir_y);
	virtual void checkPosition();
	virtual void draw(sf::RenderWindow& window);
	virtual void setDirection(int dir);

	void playerTookDamage();
	void setXY(double x, double y);
	double getX();
	double getY();
	int getHealth();
	int getDamage();
	int getDirection();
	sf::Vector2f getSpriteCenter();

	bool CheckWall();
};

class PlayerUsual : public Player //обычный игрок
{
public:
	PlayerUsual() : Player() {}
	PlayerUsual(double x, double y, double health, double damage) : Player(x, y, health, damage) {}
};

class PlayerInvisible : public Player //невидимый игрок
{
public:
	PlayerInvisible() : Player() {}
	PlayerInvisible(double x, double y, double health, double damage) : Player(x, y, health, damage) {}
	void draw(sf::RenderWindow& window) override;
};

class PlayerBoss : public Player //игрок на поле босса
{
public:
	PlayerBoss() : Player() {}
	PlayerBoss(double x, double y, double health, double damage) : Player(x, y, health, damage) {}
	void attack(Bullet* bullet, double dir_x, double dir_y, double player_x, double player_y) override;
};

class PlayerSnake : public Player //игрок который ходит как змеЮКА СУКА!
{
private:
	double snake_move_x[4] = { 0, 0, 5, -5 };
	double snake_move_y[4] = { -5, 5, 0, 0 };
	int dir = 1;
public:
	PlayerSnake() : Player() {}
	PlayerSnake(double x, double y, double health, double damage) : Player(x, y, health, damage) {}
	void movement(double dir_x, double dir_y) override;
	void checkPosition() override;
	void setDirection(int dir) override;
}; 

/* Моб */

class Mob
{
protected:
	sf::Texture mob_texture;
	sf::Sprite mob_sprite;
	sf::Vector2f movement_vector;
	double x, y, health, damage, acceleration;
	bool alive;
public:
	Mob();
	Mob(double x, double y);
	void movement();
	void updateCondition(Player* p, Bullet* b);
	void draw(sf::RenderWindow& window);
	double getX();
	double getY();
	void setXY(double x, double y);
	bool isHit();
	bool checkWall();
	int getHealth();
	int getDamage();
	sf::Vector2f getSpriteCenter();
};

class Buff //класс зелек (увеличение хп и урона)
{
protected:
	sf::Texture buff_texture;
	sf::Sprite buff_sprite;
	double x, y;
public:
	Buff();
	//virtual void BuffPlayer(Player& player);
	virtual void draw(sf::RenderWindow& window);
	void setPosition(double x, double y);
	double getX();
	double getY();
};

class Health : public Buff
{
private:
	int bonus = 5;
public:
	Health();
	//void BuffPlayer(Player& player) override;
};

class Damage : public Buff
{
private:
	int bonus = 5;
public:
	Damage();
	//void BuffPlayer(Player& player) override;
};

class Game //класс игры (тут вся отрисовка и тд)
{
private:
	Player* player = new Player();
	sf::RenderWindow window;
	sf::RenderWindow TimeWindow;
	Map* maps = new Map[4];
	int TimeInSec = 0;
	Buff* buffs[15];
	Bullet* bullet = new Bullet();
	Mob* mob = new Mob();
	int currentId;
public:
	void StartGameCycle();
	void StartTimeCycle();
	void regenerateBuff();
	bool isBuffsInCollision(Buff* buff1, Buff* buff2);
	int checkCurrId();
	void swapPlayerType();
};


class Timer //класс секундомера
{
private:
	sf::Clock clock;
	unsigned int seconds;
public:
	void StartTime();
	void EndTime();
	int GetTime();
};

class Gui //класс для создания и отображения спрайта
{
private:
	sf::Texture Texture;
	sf::Sprite Sprite;
public:
	Gui(std::string filename, int x, int y);
	void setPosition(int x, int y)
	{
		Sprite.setPosition(sf::Vector2f(x, y));
	}
	void draw(sf::RenderWindow& window);
};

class TextGui //класс для создания и отображения текста
{
private:
	sf::Font font;
	sf::Text text;
public:
	TextGui(std::string message, int size, int x, int y);
	TextGui(int message, int size, int x, int y);
	void setstring(std::string message);
	void setstring(int message);
	void setPosition(int x, int y)
	{
		text.setPosition(sf::Vector2f(x, y));
	}
	void draw(sf::RenderWindow& window);
};

class Sound
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Sound(std::string namefile, int volume);
	void ChangeVolume(int volume);
	void play();
};

class Music
{
private:
	sf::Music music;
public:
	Music(std::string namefile, int volume, bool loop);
	void ChangeVolume(int volume);
	void play();
};
