#pragma once
#include "BonusGift.h"
#include "Player.h"


//----------------------- class TimeBonusGift -----------------------
class TimeBonusGift: public BonusGift
{
public:

	// c-tor
	TimeBonusGift(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// Handle collision with player - for double dispach
	virtual void handleCollision(TimeBonusGift& gameObject) override;
	
	// Handle collision with player - let him pick you up
	virtual void handleCollision(Player& gameObject) override;

	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	virtual void handleCollision(LifeBonusGift& gameObject) override;

	virtual void handleCollision(ScoreBonusGift& gameObject) override;

private:
};

