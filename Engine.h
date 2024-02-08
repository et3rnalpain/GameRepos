#pragma once
#include "SFML/Graphics.hpp"
#include <ctime>
#include <algorithm>
//1234
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
	double x, y, ms, health, damage;
	bool invis;
public:
	Player();
	virtual void attack();
	virtual void move();
	virtual void checkPosition();
};

class PlayerUsual : public Player
{
public:
	void move() override;
};

class PlayerInvisible : public Player
{

};

class PlayerBoss : public Player
{

};

class PlayerSnake : public Player
{

};

class Game
{
private:
	Player* player;
	sf::RenderWindow window;
	Map* maps = new Map[4];
public:
	void StartGameCycle();
};