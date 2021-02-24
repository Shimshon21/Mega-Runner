#pragma once

//---------------- include section -------------------
#include "GameObject.h"
#include "Resources.h"
#include "Macros.h"

class Board;


//-------------------------- MoveObject ------------------------------
class MoveObject: public GameObject
{
public:

	// c-tor
	MoveObject(const sf::Vector2f&, Board*, const int, const int);

	// d-tor
	virtual ~MoveObject();

	// Handle collision with a ladder - climb the ladder
	virtual void handleCollision(Ladder& gameObject) override;

	// Handle collision with a pipe - hold the pipe (move on pipe)
	virtual void handleCollision(Pipe& gameObject) override;
	
	// Handle collision with a block - move back 
	virtual void handleCollision(Block& gameObject) override;


	// Handle collision with a EnemyBonusGift - virtual function.
	// only the player can collect the EnemyBonusGift.
	// EnemyBonusGift - adds an enemy to the game
	virtual void handleCollision(EnemyBonusGift& gameObject) = 0;


	// handle collision with a LifeBonusGift - virtual function.
	// only the player can collect the LifeBonusGift.
	// LifeBonusGift - adds +1 life to the player
	virtual void handleCollision(LifeBonusGift& gameObject) = 0;


	// handle collision with a ScoreBonusGift - virtual function.
	// Only the player can collect the ScoreBonusGift.
	// ScoreBonusGift - adds 10 poits to the score
	virtual void handleCollision(ScoreBonusGift& gameObject) = 0;


	// handle collision with a TimeBonusGift - virtual function.
	// only the player can collect the TimeBonusGift.
	// TimeBonusGift - adds time to the game.
	virtual void handleCollision(TimeBonusGift& gameObject) = 0;


	// check if the move is legal
	bool legalMove(const sf::Vector2f&);
	
	// move the object 
	virtual void move(const float&);

	//handle block collison on ladder.
	void handleCollisonBlockLadder(Block& gameObject);

	// set the moveObject position
	void setPosition(const float&, const float&);
	
	//Check if a moveObject is inside a hole(invisble block).
	bool isinsideBlock();

	// Return the moveObject position - the current object
	// The current object can be an enemy or a player.
	sf::Vector2f getPosition() const;

	// Return the players position in the world.
	sf::Vector2f getPlayerPos() const;

	// Return the MoveObject shape
	sf::RectangleShape getShape() const override;

	// Set the player position in the world.
	void setPlayerPos(const sf::Vector2f&);

	// Handle a fall event - fall if in air.
	virtual void handleFall( const float&) = 0;

	// Handle pipe - fall and hold the pipe correctly
	virtual void handlePipe() = 0;

protected:

	// Set the scale of m_moveObject to look like it moves left
	void setScaleLeft(const float&);


	void intializeEvents();

	// Set the scale of m_moveObject to look like it moves right
	void setScaleRight(const float&);

	// To follow acts of the object
	bool
		onLadder = false,
		onPipe = false,
		falling = false,
		onTopOfLadder = false,
		mvUp = false,
		mvDown = false,
		mvRight = false,
		mvLeft = false,
		inHandlePipe = false,
		inEnemyMove = false,
		insideBlock = false;

	// to hold the move object
	sf::RectangleShape m_moveObject;

	// old position of the player 
	sf::Vector2f m_oldPosition;

	// hold the world of the game
	Board* m_world;

private:

	//handle moveObject inside invible block.
	void handleInsideBlockEvent(Block& gameObject);

	// current position of player in world.
	sf::Vector2f m_playerPos;

};
