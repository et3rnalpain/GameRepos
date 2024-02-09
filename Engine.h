#pragma once
#include "SFML/Graphics.hpp"
#include <ctime>
#include <iostream>
#include <algorithm>

#define M_PI 3.1415926535



class Map
{
private:
	int id;
	double x, y, h = 500, w = 500;
	sf::Color color;
public:
	sf::RectangleShape rect;
	Map();
	int getId();
	void setId(int id);
	void setXY(int x_, int y_);
};


class Player
{
protected:

	sf::Texture player_texture;
	sf::Sprite player_sprite;
	double x, y, movement_speed, health, damage;
	bool invis;
public:
	Player();
	virtual void attack();
	virtual void movement(sf::Event event, sf::Time deltaTime);
	virtual void checkPosition();
	virtual void draw(sf::RenderWindow& window);
};

class PlayerUsual : public Player
{
public:
	void movement(sf::Event event, sf::Time deltaTime);
};

class PlayerInvisible : public Player
{

};

class PlayerBoss : public Player
{

};

class PlayerSnake : public Player
{
private:
	double snake_move_x[4] = { 0, 0, 2, -2 };
	double snake_move_y[4] = { -2, 2, 0, 0 };
	int direction = 3;
public:
	void movement(sf::Event event,sf::Time deltaTime) override;
	void checkPosition() override;
}; 

class Buff
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

class Game
{
private:
	Player* player = new PlayerSnake(); //мен€йте на змею, если хотите протестить
	sf::RenderWindow window;
	sf::RenderWindow TimeWindow;
	Map* maps = new Map[4];
	int TimeInSec = 0;
	//Damage dbuffs[10];
	//Health hbuffs[10];
public:
	void StartGameCycle();
	void StartTimeCycle();
};


class Timer
{
private:
	sf::Clock clock;
	unsigned int seconds;
public:
	void StartTime();
	void EndTime();
	int GetTime();
};

