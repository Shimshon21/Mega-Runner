#pragma once
#include "Enemy.h"


class NormalEnemy: public Enemy
{
public:

	// c-tor
	NormalEnemy(const sf::Vector2f&, Board*, const int, const int);

	// d-tor
	~NormalEnemy();

	// move the nortmal enemy
	virtual void move(const float&);

private:

	// To hold the next move
	int m_move = 0;

	// To switch to the next move every X seconds
	sf::Clock m_timer;
};
