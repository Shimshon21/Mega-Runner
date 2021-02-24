#include "TrackingEnemy.h"
#include <cmath>

// c-tor
TrackingEnemy::TrackingEnemy(const sf::Vector2f& position,
	Board* world, const int height, const int width)
	: Enemy(position, world, height, width) 
{}


// d-tor
TrackingEnemy::~TrackingEnemy()
{}


//---------------------------- move ---------------------------------
// Move the tracking enemy.
// The next movement of the tracking enemy is calculated as follows:
// 1. With the help of the auxillary function getDistance() calculates
// all the posible distances between the player position and the enemy 
// position after doin a X movement.
// 2. Returns(with the function minDistance) the distance that gave
// the minimum distance between the player position and the player
// position.
// 3. Gets the requered movement and d1,...,d4 and return the 
// appropriate movement type.
// 4. The function getNextMove with that type return the next 
// required movement.
// 5. The function legalMove checks whether the next move is legal 
// or not.
// 6. After after performing the next movement, we exucute the 
// function handeEvents(That uses double dispach) that runs over
// the obecjts of the world and checks if the enemy collides with
// one of the objects of the world.
//-------------------------------------------------------------------
void TrackingEnemy::move(const float& deltaTime)
{
	inEnemyMove = true;

	// to hold the wanted movement and then
	// check if the movement is okay or not 
	auto movement = sf::Vector2f(0, 0);
	mvUp = mvDown = mvLeft = mvRight = false;

	double 
		// 1 - up
		d1 = getDistance
		(sf::Vector2f(0, -(CONSTANT_ENEMY_SPEED * deltaTime))),  
		// 2 - down
		d2 = getDistance
		(sf::Vector2f(0, (CONSTANT_ENEMY_SPEED * deltaTime))),	  
		 // 3 - left
		d3 = getDistance
		(sf::Vector2f(-(CONSTANT_ENEMY_SPEED * deltaTime), 0)),	   
		 // 4 - right
	    d4 = getDistance
		(sf::Vector2f((PLAYER_SPEED * deltaTime), 0));			   


	if (!falling)	  // If falling then skip
	{
		movement = getNextMove(minDistance(d1, d2, d3, d4), deltaTime);
	}


	// if the movement was legal, move the player
	if (legalMove(movement))
	{
		m_oldPosition = m_moveObject.getPosition();
		m_moveObject.move(movement);
	}

	// intialize special events
	intializeEvents();

	// handle all the events
	handleEvents();

	inEnemyMove = false;
}


//-------------------- getDistance ----------------------
//   Return the distance between two given positions
//-------------------------------------------------------
int TrackingEnemy::getDistance(const sf::Vector2f& move)
{
	auto playerPos = getPlayerPos();
	auto enemyPos = m_moveObject.getPosition() + move;

	return sqrt(pow((playerPos.x - enemyPos.x), 2) +
		pow((playerPos.y - enemyPos.y), 2));
}



//---------------------------- minDistance ----------------------------
// Calculate which movement of the enemy returns the shortest distance
// between the player and the enemy.
//---------------------------------------------------------------------
int TrackingEnemy::minDistance(const double& d1, const double& d2,
	const double& d3, const double& d4)
{

	// allow to move up only if the enemy is on ladder.
	if (onLadder) 
	{
		// signal to move up
		if (d1 <= d2 && d1 <= d3 && d1 <= d4 ||
			m_moveObject.getPosition().y > getPlayerPos().y)
			return 1;
	}

	// signal to move down
	if (d2 <= d1 && d2 <= d3 && d2 <= d4)
		return 2;

	// signal to move left
	if (d3 <= d1 && d3 <= d2 && d3 <= d4)
		return 3;

	// signal to move right
	if (d4 <= d1 && d4 <= d2 && d4 <= d3)
		return 4;

	// default
	return 0;
}


//--------------------- getNextMove -----------------------
// Return the next movement the tracking enemy should do.
// Calculates the next movement with the given params.
//---------------------------------------------------------
sf::Vector2f TrackingEnemy::getNextMove(const int& type, 
	const float& deltaTime)
{
	// to hold the wanted movement and then
	// check if the movement is okay or not 
	auto movement = sf::Vector2f(0, 0);

	switch (type)
	{
	case UP:
		// move up
		if (onLadder)
		{
			mvUp = true;
			movement.x = 0;
			movement.y = -(TRACKING_ENEMY_SPEED * deltaTime);
		}
		break;

	case DOWN:
		// move down
		mvDown = true;
		movement.x = 0;
		movement.y = (TRACKING_ENEMY_SPEED * deltaTime);
		break;

	case LEFT:
		// move left
		mvLeft = true;
		setScaleLeft(m_moveObject.getScale().y);
		movement.x = -(TRACKING_ENEMY_SPEED * deltaTime);
		movement.y = 0;
		break;

	case RIGHT:
		// move right
		mvRight = true;
		setScaleRight(m_moveObject.getScale().y);
		movement.x = (TRACKING_ENEMY_SPEED * deltaTime);
		movement.y = 0;
		break;
	}

	// Return the next morement
	return movement;
}
