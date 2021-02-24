#pragma once

//------------------ includes -----------------
#include "MoveObject.h"
#include "Macros.h"
#include "Board.h"


//-------------------- Class Player --------------------
class Player : public MoveObject
{
public:

	// c -tor
	Player(const sf::Vector2f&, Board*, const int, const int);

	// d-tor
	virtual ~Player();

	// handle collision with a game object
	virtual void handleCollision(GameObject& gameObject);

	// handle collision with a player - does nothing.
	virtual void handleCollision(Player& gameObject) override;

	// handle collision with a enemy - restart the stage.
	virtual void handleCollision(Enemy& gameObject)override;

	// Handle collision with a block - move backwards
	virtual void handleCollision(Block& gameObject) override;

	// Handle collision with a ladder - climb the ladder
	virtual void handleCollision(Ladder& gameObject) override;

	// Handle collision with a pipe - hold the pipe (move on pipe)
	virtual void handleCollision(Pipe& gameObject) override;

	// handle collision with a coin - collect the coin
	virtual void handleCollision(Coin& gameObject) override;

	// handle collision with a EnemyBonusGift - collect the gift
	virtual void handleCollision(EnemyBonusGift& gameObject) override;

	// handle collision with a LifeBonusGift - collect the gift
	virtual void handleCollision(LifeBonusGift& gameObject) override;

	// handle collision with a ScoreBonusGift - collect the gift
	virtual void handleCollision(ScoreBonusGift& gameObject) override;

	// handle collision with a TimeBonusGift - collect the gift
	virtual void handleCollision(TimeBonusGift& gameObject) override;

	// move the player
	void move(const float&);

	// draw the player obejct
	// (more info in function definition)
	virtual void draw(sf::RenderWindow& window) override;

	// return the score
	int getScore() const;

	// Return if the player got hit by enemy
	bool isPlayerGotHit() const;

	// Add bouns to the current score 
	void stageBonusAddScore();

	// decrease the score
	void decreaseStageScore();

	// Rest the score of the player
	void resetScore();

	// Return the amount of lifes left
	int getLifes() const;

	// Reset the number of coins
	void resetCoins();

	// Return the amount of coins collected
	int getCoins() const;

	// Rest the life of the player
	void resetLife();

	// Increase the amount of life by 1
	void increaseLife();

	// Decrease the amount of life by 1
	void decLifeByOne();

	// Sets the time
	void setTime(int* time);

	// Handle time events 
	void handleTimeEvents();

	// handle the fall event of the player.
	virtual void handleFall( const float&) override;

	// Handle pipe - the player falls and holds
	// the pipe correctly
	virtual void handlePipe() override;

private:

	// handle all the avaible events
	void handleEvents();

	// Return the next requested movement
	sf::Vector2f getMove(const float&);

	// Auxillary function to set the texture inrects
	void setTextureInrect();

	// Handle the situation of being on top of a ladder
	void handleOnTopOfLadder();

	// Handle a dig action when being on top of ladder
	void handleDigOnladder();
	
	// set animation
	void setAnimation();

	// Player digging the floor
	void digFloor();

	// The player digs the left floor 
	void digLeftFloor(sf::Vector2f position);

	// The player digs the Right floor 
	void digRightFloor(sf::Vector2f position);

	// Draw the on ladder animation
	void onLadderAnimation();

	// Draw the running animation
	void runningAnimation();

	// Draw the falling animation
	void fallingAnimation();

	// Draw the digging animation
	void digAnimation();

	// Draw the staning animation
	void standingAnimation();

	// Draw the new enemy animation 
	void insertEnemyAnimation();


	// Set the size and the texture of a new enemy 
	// apearing in the game  when the player picks 
	// up an enemy gift.
	void setEnemyGiftCharacteristics();

	// to hold the data of  player in real time
	static int m_score,
		m_lifes;

	int m_coins = 0, 
		m_bonusGiftScore = 0,
		* m_time;

	sf::Clock addEnemyTimer;

	// to follow the acts the 
	//player did and act accordingly
	bool digTheFloor = false,
		digLeft = false,
		digRight = false, 
		hitEnemy = false,
		insertEnemy = false;

	sf::Vector2f addNewEnemyPos;

	// animation texture 
	// -> takes parts of the texture
	sf::IntRect
		rectSourceTextureRunning,
		rectSourceTextureFalling,
		rectSourceTextureStrike,
		rectSourceTextureStanding,
		rectSourceTextureClimbing;

	// animation timer
	sf::Clock timeAnimation;


	//new enemy texture
	sf::RectangleShape newEnemy;
	sf::IntRect rectSourceTextureNewEnemy;
	sf::Clock newEnemyTimer;
};