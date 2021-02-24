#include "TimeBonusGift.h"
#include "..\include\TimeBonusGift.h"


// c-tor
TimeBonusGift::TimeBonusGift(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture)
	:BonusGift(height, width, position, texture)
{}


//------------------- handleCollision -----------------------
//     Handle collision with player - for double dispach
//-----------------------------------------------------------
void TimeBonusGift::handleCollision(TimeBonusGift& gameObject)
{
	gameObject.handleCollision(*this);
}


//------------------- handleCollision -----------------------
//     Handle collision with player - let him pick you up
//-----------------------------------------------------------
void TimeBonusGift::handleCollision(Player& gameObject)
{
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}


void TimeBonusGift::handleCollision(EnemyBonusGift& gameObject) {}

void TimeBonusGift::handleCollision(LifeBonusGift& gameObject) {}

void TimeBonusGift::handleCollision(ScoreBonusGift& gameObject) {}