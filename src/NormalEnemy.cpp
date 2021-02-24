#include "NormalEnemy.h"


// c-tor
NormalEnemy::NormalEnemy(const sf::Vector2f& position, Board* world,
	const int height, const int width)
	:Enemy(position, world, height, width)
{


}

// d-tor
NormalEnemy::~NormalEnemy()
{}


//-------------------------- move ---------------------------
// Move the noraml enemy.
// Every 0.5 seconds, a new movement is selected.
// The new movement is a random move.
// After getting a new movement, check if the new movement 
// is legal.
// If the next movement was legal, check (with the function
// handleEvents that does double dispach) if the enemy
// collides with another object of the game
//----------------------------------------------------------
void NormalEnemy::move(const float& deltaTime)
{
	// to hold the wanted movement and then
	// check if the movement is okay or not 
	auto movement = sf::Vector2f(0, 0);
	mvUp = mvDown = mvLeft = mvRight = false;


	// swich to another movement every 0.5 seconds
	if (m_timer.getElapsedTime().asSeconds() >= 0.5)
	{
		m_move = (rand() % 4) + 1;
		m_timer.restart();
	}

	switch (m_move)
	{
	case  UP:
		if (onLadder)
		{
			mvUp = true;
			movement.x = 0;
			movement.y = -(CONSTANT_ENEMY_SPEED * deltaTime);
		}
		break;

	case DOWN:
		mvDown = true;
			movement.x = 0;
			movement.y = (CONSTANT_ENEMY_SPEED * deltaTime);
		break;

	case  LEFT:
		if (!falling)
		{
			mvLeft = true;
			setScaleLeft(ENEMY_SCALE);
			movement.x = -(CONSTANT_ENEMY_SPEED * deltaTime);
			movement.y = 0;
		}
		break;
	
	case RIGHT:
		if (!falling)
		{
			mvRight = true;
			setScaleRight(ENEMY_SCALE);
			movement.x = (CONSTANT_ENEMY_SPEED * deltaTime);
			movement.y = 0;
		}
		break;
	}


	// if the movement was legal, move the player
	if (legalMove(movement))
	{
		m_oldPosition = getPosition();
		m_moveObject.move(movement);
	}


	// intialize special events
	intializeEvents();

	// handle all the events
	handleEvents();
}

