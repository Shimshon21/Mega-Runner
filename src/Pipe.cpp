#include "Pipe.h"
#include "Macros.h"
#include "Enemy.h"


// c-tor
Pipe::Pipe(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture):
	StaticObject(height, width,
		sf::Vector2f(position.x,(position.y+ height*0.2)), texture)
{}


// d-tor
Pipe::~Pipe()
{}


//----------------------- handleCollision ---------------------------
// Handle collision with an object of the game - for double dispach 
//-------------------------------------------------------------------
void Pipe::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}


//------------------ handleCollision --------------------
// Handle collision with player - let him move on you
//------------------------------------------------------
void Pipe::handleCollision(Player& gameObject)
{
	handleCollision((GameObject&)gameObject);
}


//------------------ handleCollision --------------------
// Handle collision with enemy - let him move on you
//------------------------------------------------------
void Pipe::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}


void Pipe::handleDig(sf::Vector2f position) {}


void Pipe::handleCollision(Ladder& gameObject) {}


void Pipe::handleCollision(Block& gameObject) {}


void Pipe::handleCollision(Coin& gameObject) {}


void Pipe::handleCollision(Pipe& gameObject) {}


void Pipe::handleCollision(EnemyBonusGift& gameObject) {}


void Pipe::handleCollision(LifeBonusGift& gameObject) {}


void Pipe::handleCollision(ScoreBonusGift& gameObject) {}


void Pipe::handleCollision(TimeBonusGift& gameObject) {}

