#pragma once
#include "SFML/Graphics.hpp"
#include <ctime>
#include <algorithm>

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
	sf::RectangleShape player_shape;
	sf::Texture player_texture;
	sf::Sprite player_sprite;
	double x, y, movement_speed, health, damage;
	bool invis;
public:
	Player();
	virtual void attack();
	virtual void movement(sf::Event event);
	virtual void checkPosition();
	virtual void draw(sf::RenderWindow& window);
};

class PlayerUsual : public Player
{
public:
	void movement(sf::Event event) override;
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
	double snake_move_x[4] = { 0, 0, 0.1, -0.1 };
	double snake_move_y[4] = { -0.1, 0.1, 0, 0 };
	int direction = 3;
public:
	void movement(sf::Event event) override;
	void checkPosition() override;
}; 

class Game
{
private:
	Player* player = new PlayerUsual(); //мен€йте на змею, если хотите протестить
	sf::RenderWindow window;
	Map* maps = new Map[4];
public:
	void StartGameCycle();
};

class Buff 
{
protected:
	sf::RectangleShape buff_shape;
	sf::Texture buff_texture;
public:
	Buff();
	virtual void BuffPlayer(Player& player);
};

class Health : public Buff 
{
private:
	int bonus = 5;
public:
	void BuffPlayer(Player& player) override;
};

class Damage : public Buff
{
private:
	int bonus = 5;
public:
	void BuffPlayer(Player& player) override;
};