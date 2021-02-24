#include "Block.h"
#include "Macros.h"
#include "Enemy.h"
#include "Player.h"


// c-tor
Block::Block(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture)
	:StaticObject(height, width, position, texture)
{}


// d-tor
Block::~Block()
{}


//---------------------------- draw --------------------------------- 
//                  Draw the block on the window. 
//-------------------------------------------------------------------
void Block::draw(sf::RenderWindow & window)
{
	if (invisible) {
		if (m_invisbleTimer.getElapsedTime().asSeconds() >= 4.0f)
		{
			setFillColor(sf::Color::White);
			invisible = false;
		}
	}

	// draw the block object on the window
	window.draw(getShape());
}


//---------------------- handleDig --------------------------
// The blocks handles a dig situation. 
// If the players wants to dig the floor, the block sets his
// color to Transparent and disappears from the world.
// The block returns back (return it's normal texture) after
// 5 seconds.
// If the player stands on top of the Transparent block, he 
// falls down. 
// If the enemy stands on top of the Transparent block,
// he falls and stays between the 2 blocks.
//-----------------------------------------------------------
void Block::handleDig(sf::Vector2f position)
{
	if (getShape().getGlobalBounds().contains(position))
	{
		invisible = true;
		m_invisbleTimer.restart();
		setFillColor(sf::Color::Transparent);
	}
}


//--------------- isSomeoneInside ---------------
// Return if moveable object is inside the block
//-----------------------------------------------
bool Block::isSomeoneInside()
{
	return someoneInside;
}


//--------------- setSomeOneInside ---------------
// Sets a moveObject inside the the "hole".
//------------------------------------------------
void Block::setSomeOneInside(const bool isInside)
{
	someoneInside = isInside;
}


//--------------------- handleCollision --------------------
// handle collision with a game object - for double dispach
//----------------------------------------------------------
void Block::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}


//-------------------- handleCollision -------------------
// handle collision with a a move object - move him back
// Calls the function of the moving objectand thus informs
// it that it must move backwards
//--------------------------------------------------------
void Block::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}


//-------------------- handleCollision --------------------
// handle collision with a a move object - move him back
// Calls the function of the moving objectand thus informs
// it that it must move backwards
//---------------------------------------------------------
void Block::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}


void Block::handleCollision(Ladder& gameObject) {}


void Block::handleCollision(Block& gameObject) {}


void Block::handleCollision(Coin& gameObject) {}


void Block::handleCollision(Pipe& gameObject) {}


void Block::handleCollision(EnemyBonusGift& gameObject) {}


void Block::handleCollision(LifeBonusGift& gameObject) {}


void Block::handleCollision(ScoreBonusGift& gameObject) {}


void Block::handleCollision(TimeBonusGift& gameObject) {}

