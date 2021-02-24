#include "ScoreBonusGift.h"

// c-tor
ScoreBonusGift::ScoreBonusGift(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture)
	:BonusGift(height, width, position, texture)
{}


//--------------------- handleCollision ------------------------
// Handle collision with player - let him pick you up and 
// afterward dispose form the world of the game
//--------------------------------------------------------------
void ScoreBonusGift::handleCollision(Player& gameObject)
{
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}


//--------------------- handleCollision ------------------------
// Handle collision with gameObject - for Double Dispach 
//--------------------------------------------------------------
void ScoreBonusGift::handleCollision(ScoreBonusGift& gameObject)
{
	gameObject.handleCollision(*this);
}


void ScoreBonusGift::handleCollision(EnemyBonusGift& gameObject) {}


void ScoreBonusGift::handleCollision(LifeBonusGift& gameObject) {}


void ScoreBonusGift::handleCollision(TimeBonusGift& gameObject) {}
