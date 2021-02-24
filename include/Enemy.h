#pragma once
#include"MoveObject.h"


//------------------------- class enemy ----------------------------
class Enemy: public MoveObject
{
public:

	// c-tor
	Enemy(const sf::Vector2f&, Board*, const int height, const int width);

	// d-tor
	virtual ~Enemy();

	// move the enemy objects - virtual function
	virtual void move(const float&);

	// virtual draw function to draw the enemy
	virtual void draw(sf::RenderWindow& window);

	// handle the fall event of the enemy.
	virtual void handleFall( const float&) override;

	// Handle pipe - the enemy falls and holds the pipe correctly
	virtual void handlePipe() override;

	// Handle collision with a ladder - climb the ladder
	virtual void handleCollision(Ladder& gameObject) override;

	// Handle collision with a pipe - hold the pipe (move on pipe)
	virtual void handleCollision(Pipe& gameObject) override;
	
	// Handle collision with block - push back
	virtual void handleCollision(Block& gameObject) override;

	virtual void handleCollision(GameObject& gameObject);

	virtual void handleCollision(Player& gameObject) override;

	virtual void handleCollision(Enemy& gameObject) override;

	virtual void handleCollision(Coin& gameObject) override;

	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	virtual void handleCollision(LifeBonusGift& gameObject) override;

	virtual void handleCollision(ScoreBonusGift& gameObject) override;

	virtual void handleCollision(TimeBonusGift& gameObject) override;

protected:

	// Handle the situation of being on top of a ladder
	void handleOnTopOfLadder();

	// handle all possible events in the game.
	void handleEvents();

private:

	// set animation
	void setAnimation();
	
	// Auxillary function to set the texture inrects
	void setTextureInrect();

	// Draw the enemy running 
	void runningAnimation();

	// Draw the enemy climbing a ladder 
	void climbingAnimation();

	// Inrects of enemy textures - for animation
	sf::IntRect rectSourceTextureRunning,
		recSourceTextureClimb,
		recSourceTextureClimbing,
		recSourceTexturePipe;

	// animation timer
	sf::Clock timeAnimation;
};

