#pragma once
#include"ConstantEnemy.h"
#include "Enemy.h"


//-------------- class ConstantEnemy -----------------
class ConstantEnemy: public Enemy
{
public:

	// c-tor
	ConstantEnemy(const sf::Vector2f&, Board*,
		const int height, const int width);

	// d-tor
	virtual ~ConstantEnemy();
	
	// moves the Enemy - constant move 
	virtual void move(const float&);

private:

	// Return the next move of the constant enemy
	sf::Vector2f getMove(const float&);
};
