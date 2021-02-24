#pragma once
#include "StaticObject.h"


//-------------------------- class ladder ---------------------------
class Ladder:public StaticObject
{
public:

	// c-tor
	Ladder(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// d-tor
	virtual ~Ladder();

private:

	// Handle collision with an object of the game - for double dispach
	virtual void handleCollision(GameObject& gameObject) override;

	// handle collision with player - let him climb up
	virtual void handleCollision(Player& gameObject) override;
	
	virtual void handleDig(sf::Vector2f position) override;

	virtual void handleCollision(Enemy& gameObject) override;

	virtual void handleCollision(Ladder& gameObject) override;

	virtual void handleCollision(Block& gameObject) override;

	virtual void handleCollision(Coin& gameObject) override;

	virtual void handleCollision(Pipe& gameObject) override;

	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	virtual void handleCollision(LifeBonusGift& gameObject) override;

	virtual void handleCollision(ScoreBonusGift& gameObject) override;

	virtual void handleCollision(TimeBonusGift& gameObject) override;
};
