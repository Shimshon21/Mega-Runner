#pragma once
#include "StaticObject.h"

//----------------------- class coin ---------------------------
class Coin :public StaticObject
{
public:

	// c-tor
	Coin(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// d-tor
	virtual ~Coin();

	// Draw the coin on the window
	virtual void  draw(sf::RenderWindow& window)  override;

	// Handle collistion with an object  - for double dispach
	virtual void handleCollision(GameObject& gameObject) override;

	// Handle collistion with player - let him collet you
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

private:

	// set animation
	void setAnimation();

	// animation texture 
	// -> takes parts of the texture
	sf::IntRect rectSourceTexture;

	// animation timer
	sf::Clock timeAnimation;
};