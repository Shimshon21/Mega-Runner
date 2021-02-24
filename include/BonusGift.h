#pragma once
#include "StaticObject.h"



//---------------- include section -------------------
#include "StaticObject.h"
#include "Macros.h"


//----------------------- class BonusGift --------------------------
class BonusGift :public StaticObject
{
public:

	// c-tor
	BonusGift(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// d-tor
	virtual ~BonusGift();

	// draw the gift on the window
	virtual void draw(sf::RenderWindow& window) override;

	// handle collision with an object - for double dispach
	virtual void handleCollision(GameObject& gameObject) override;

	virtual void handleCollision(Player& gameObject) = 0;
	
	virtual void handleDig(sf::Vector2f position) override;

	virtual void handleCollision(Enemy& gameObject) override;

	virtual void handleCollision(Ladder& gameObject) override;

	virtual void handleCollision(Block& gameObject) override;

	virtual void handleCollision(Coin& gameObject) override;

	virtual void handleCollision(Pipe& gameObject) override;

	virtual void handleCollision(EnemyBonusGift& gameObject) = 0;

	virtual void handleCollision(LifeBonusGift& gameObject) = 0;

	virtual void handleCollision(ScoreBonusGift& gameObject) = 0;

	virtual void handleCollision(TimeBonusGift& gameObject) = 0;

private:

	// set animation
	void setAnimation();

	// animation texture 
	// -> takes parts of the texture
	sf::IntRect rectSourceTexture;

	// animation timer
	sf::Clock timeAnimation;
};

