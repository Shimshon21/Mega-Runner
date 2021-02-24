#pragma once
#include "Enemy.h"


//-------------------------- class TrackingEnemy -----------------------
class TrackingEnemy: public Enemy
{
public:

	// c-tor
	TrackingEnemy(const sf::Vector2f&, Board*, const int, const int);

	// d-tor
	~TrackingEnemy();
	
	// Move the Tracking enemy 
	virtual void move(const float&);

private:

	// Return distance between the enemy and the player
	int getDistance(const sf::Vector2f&);

	// Return the minmum distance between the
	// enemy and the player
	int minDistance(const double&, const double&,
		const double&, const double&);

	// Return the next move of the tracking enemy
	sf::Vector2f getNextMove(const int&, const float&);
};
