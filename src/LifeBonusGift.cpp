#include "LifeBonusGift.h"


// c-tor
LifeBonusGift::LifeBonusGift(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture) :
	BonusGift(height, width, position, texture)
{}


//--------------------- handleCollision ----------------------
// Handle collision - for Double Dispach
//------------------------------------------------------------
void LifeBonusGift::handleCollision(LifeBonusGift& gameObject)
{
	gameObject.handleCollision(*this);
}


//------------------ handleCollision ---------------------
// Handle collision with player - let him pick you up
// and dispose from the world of the game
//--------------------------------------------------------
void LifeBonusGift::handleCollision(Player& gameObject)
{
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}


void LifeBonusGift::handleCollision(EnemyBonusGift& gameObject) {}


void LifeBonusGift::handleCollision(ScoreBonusGift& gameObject) {}


void LifeBonusGift::handleCollision(TimeBonusGift& gameObject) {}
