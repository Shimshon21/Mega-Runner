#pragma once
#include "BonusGift.h"
#include "Player.h"

class LifeBonusGift : public BonusGift
{
public:

	// c-tor
	LifeBonusGift(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// Handle collision with player - let him pick you up
	virtual void handleCollision(Player& gameObject);

	// Handle collision - for Double Dispach
	virtual void handleCollision(LifeBonusGift& gameObject) override;
	
	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	virtual void handleCollision(ScoreBonusGift& gameObject) override;

	virtual void handleCollision(TimeBonusGift& gameObject) override;

private:

};