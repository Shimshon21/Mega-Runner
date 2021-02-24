#include "EnemyBonusGift.h"


// c-tor
EnemyBonusGift::EnemyBonusGift(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture)
	:BonusGift(height, width, position, texture)
{}


//------------------- handleCollision -------------------
// Handle collision with player - let him pick you up
//-------------------------------------------------------
void EnemyBonusGift::handleCollision(Player & gameObject)
{
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}


//--------------------- handleCollision ------------------------
//           For double dispach - Return to player
//--------------------------------------------------------------
void EnemyBonusGift::handleCollision(EnemyBonusGift& gameObject)
{
	gameObject.handleCollision(*this);
}


void EnemyBonusGift::handleCollision(LifeBonusGift& gameObject) {}


void EnemyBonusGift::handleCollision(ScoreBonusGift& gameObject) {}


void EnemyBonusGift::handleCollision(TimeBonusGift& gameObject) {}


