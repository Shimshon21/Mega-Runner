#pragma once
#include "StaticObject.h"


//------------------------- class Block ------------------------
class Block :public StaticObject
{
public:

	// c-tor 
	Block(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// d-tor
	virtual ~Block();

	// Draw the block on the window.
	virtual void draw(sf::RenderWindow& window) override;

	// Handles the dig action of the player.
	virtual void handleDig(sf::Vector2f position) override;
	
	// Returns if someone is inside the "hole".
	bool isSomeoneInside();

	// Sets a moveObject inside the the "hole".
	void setSomeOneInside(const bool isInside);

	// Handle collision with a game object - for double dispach
	virtual void handleCollision(GameObject& gameObject) override;

	// Handle collision with a moveObject - move him back
	virtual void handleCollision(Player& gameObject) override;

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

	// Timer for the digging of the block.
	sf::Clock m_invisbleTimer;

	// To raise a flag if the block 
	bool invisible = false,someoneInside = false;
};

