#pragma once
#include "StaticObject.h"


//------------------------- class pipe ----------------------------
class Pipe:public StaticObject
{
public:
	// c-tor
	Pipe(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);
	
	//d-tor
	virtual ~Pipe();
	
	// Handle collision with an object of the game - for double dispach
	virtual void handleCollision(GameObject& gameObject) override;

	// Handle collision with player - let him move on you
	virtual void handleCollision(Player& gameObject) override;
	
	// Handle collision with enemy - let him move on you
	virtual void handleCollision(Enemy& gameObject) override ;
	
	virtual void handleDig(sf::Vector2f position) override;

	virtual void handleCollision(Ladder& gameObject) override;

	virtual void handleCollision(Block& gameObject) override;

	virtual void handleCollision(Coin& gameObject) override;

	virtual void handleCollision(Pipe& gameObject) override;

	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	virtual void handleCollision(LifeBonusGift& gameObject) override;

	virtual void handleCollision(ScoreBonusGift& gameObject) override;

	virtual void handleCollision(TimeBonusGift& gameObject) override;

private:

};