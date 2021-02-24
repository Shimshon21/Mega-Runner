#pragma once
#include"BonusGift.h"
#include "Player.h"


class EnemyBonusGift:public BonusGift
{
public:
	// c-tor
	EnemyBonusGift(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// Handle collision with player - let him pick you up
	virtual void handleCollision(Player& gameObject) override;

	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	virtual void handleCollision(LifeBonusGift& gameObject) override;

	virtual void handleCollision(ScoreBonusGift& gameObject) override;

	virtual void handleCollision(TimeBonusGift& gameObject) override;

private:
};