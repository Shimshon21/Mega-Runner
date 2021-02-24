#include "Ladder.h"
#include "Macros.h"
#include "Player.h"
#include "Enemy.h"

// c-tor
Ladder::Ladder(const int height, const int width,
	sf::Vector2f position, sf::Texture * texture) :
	StaticObject(height, width, position, texture)
{}

// d-tor
Ladder::~Ladder() {}


//---------------------- handleCollision ---------------------------
// Handle collision with an object of the game - for double dispach
//------------------------------------------------------------------
void Ladder::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}


//---------------------- handleCollision ---------------------------
// handle collision with an moveObject - let him climb up and down
//------------------------------------------------------------------
void Ladder::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}


//---------------------- handleCollision ---------------------------
// handle collision with an moveObject - let him climb up and down
//------------------------------------------------------------------
void Ladder::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}


void Ladder::handleDig(sf::Vector2f position) {}


void Ladder::handleCollision(Ladder& gameObject) {}


void Ladder::handleCollision(Block& gameObject) {}


void Ladder::handleCollision(Coin& gameObject) {}


void Ladder::handleCollision(Pipe& gameObject) {}


void Ladder::handleCollision(EnemyBonusGift& gameObject){}


void Ladder::handleCollision(LifeBonusGift& gameObject) {}


void Ladder::handleCollision(ScoreBonusGift& gameObject) {}


void Ladder::handleCollision(TimeBonusGift& gameObject) {}
