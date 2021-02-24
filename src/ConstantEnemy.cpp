#include "ConstantEnemy.h"


// c-tor
ConstantEnemy::ConstantEnemy(const sf::Vector2f& position,
	Board* world, const int height, const int width)
	: Enemy(position, world, height, width)
{
	m_moveObject.setOutlineColor(sf::Color::Blue);
}



// d-tor
ConstantEnemy::~ConstantEnemy()
{}


//---------------------- move ---------------------------
// moves the Enemy - constant move
// Move the enemy to the right side or to the left size
//-------------------------------------------------------
void ConstantEnemy::move(const float& deltalTime)
{
	static sf::Clock gameMovementClock;
	// intialize special events
	onLadder = false;
	onPipe = false;

	if (!falling)
	{
		// Get the next movement
		auto movement = getMove(deltalTime);

		// Check if the movement is legal
		if (legalMove(movement))
		{
			mvLeft = mvRight = true;
			m_moveObject.move(movement);
			handleEvents();
		}
	}
}


//------------------------- getMove ------------------------------
// Return the next move of the player.
// The next move is selected by the time passed. 
// The Constant Enemy changes it's scale every X seconds.
//----------------------------------------------------------------
sf::Vector2f ConstantEnemy::getMove(const float& deltalTime)
{
	// static timer to have the movement every X time
	static sf::Clock gameMovementClock;

	// side we need to scale
	bool scaleLeft = true;                  
	bool scaleRight = true;


	auto moveLeft = sf::Vector2f                    // left move
	(-(CONSTANT_ENEMY_SPEED)*deltalTime, 0);

	auto moveRIght = sf::Vector2f					// right move
	((CONSTANT_ENEMY_SPEED)*deltalTime, 0);


	// If the number of seconds is less or equal to 2, then move left
	if (gameMovementClock.getElapsedTime().asSeconds() <=
		CONSTANT_ENEMY_MOVE_LEFT)
	{
		if (scaleLeft)
		{
			setScaleLeft(m_moveObject.getScale().y);
		}
		return moveLeft; 
	}
	// If the number of seconds is bigger than 2
	// and less or equal to 4, then move right
	else if (gameMovementClock.getElapsedTime().asSeconds() <=
		CONSTANT_ENEMY_MOVE_RIGHT)
	{
		setScaleRight(m_moveObject.getScale().y);
		return moveRIght;
	}
	// If the time is greater than 4, move left
	// again and reset the timer
	else
	{
		gameMovementClock.restart();
		setScaleLeft(m_moveObject.getScale().y);
		return moveLeft;
	}


	// default
	return moveLeft;
}



