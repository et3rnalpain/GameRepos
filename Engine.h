#pragma once
#include "SFML/Graphics.hpp"
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

#define M_PI 3.1415926535



class Map //класс карты
{
private:
	int id;
	double x, y, h = 500, w = 500;
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
	Player(double x, double y);
	Player(const Player& player);
	virtual void attack();
	virtual void movement(double dir_x, double dir_y);
	virtual void checkPosition();
	virtual void draw(sf::RenderWindow& window);
	double getX();
	double getY();
	void setXY(double x, double y);
	bool CheckWall();
	int getHealth();
	int getDamage();
};

class PlayerUsual : public Player //обычный игрок
{
public:
	PlayerUsual() : Player() {}
	PlayerUsual(double x, double y) : Player(x, y) {}
};

class PlayerInvisible : public Player //невидимый игрок
{
public:
	PlayerInvisible() : Player() {}
	PlayerInvisible(double x, double y) : Player(x,y) {}
};

class PlayerBoss : public Player //игрок на поле босса
{
public:
	PlayerBoss() : Player() {}
	PlayerBoss(double x, double y) : Player(x, y) {}
};

class PlayerSnake : public Player //игрок который ходит как змеЮКА СУКА!
{
private:
	double snake_move_x[4] = { 0, 0, 2, -2 };
	double snake_move_y[4] = { -2, 2, 0, 0 };
	int direction = 1;
public:
	PlayerSnake() : Player() {}
	PlayerSnake(double x, double y) : Player(x, y) {}
	void movement(double dir_x, double dir_y) override;
	void checkPosition() override;
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
	int currentId;
public:
	void StartGameCycle();
	void StartTimeCycle();
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

