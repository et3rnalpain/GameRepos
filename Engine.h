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
	double getX();
	double getY();
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
	Player(const Player& player);
	virtual void attack();
	virtual void movement(sf::Event event, sf::Time deltaTime);
	virtual void checkPosition();
	virtual void draw(sf::RenderWindow& window);
	double getX();
	double getY();
	bool CheckWall();
	int getHealth();
	int getDamage();
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
	Player* player = new PlayerUsual(); //������� �� ����, ���� ������ ����������
	sf::RenderWindow window;
	sf::RenderWindow TimeWindow;
	Map* maps = new Map[4];
	int TimeInSec = 0;
	Buff* buffs[15];
public:
	void StartGameCycle();
	void StartTimeCycle();
	void swapPlayerType();
	bool isChangedPosition();
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

class Gui
{
private:
	sf::Texture Texture;
	sf::Sprite Sprite;
public:
	Gui(std::string filename, int x, int y);
	void draw(sf::RenderWindow& window);
};

class TextGui
{
private:
	sf::Font font;
	sf::Text text;
public:
	TextGui(std::string message, int size, int x, int y);
	TextGui(int message, int size, int x, int y);
	void draw(sf::RenderWindow& window);
};

