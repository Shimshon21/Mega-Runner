#include "BonusGift.h"
#include "Player.h"
#include "Macros.h"


// c-tor
BonusGift::BonusGift(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture)
	:StaticObject(height, width, position, texture)
{
	rectSourceTexture = sf::IntRect(0, 0, GIFT_WIDTH, GIFT_HEIGHT);
}


// d-tor
BonusGift::~BonusGift()
{}


//-------------------- draw --------------------
// Draw the gift object on the window.
//----------------------------------------------
void BonusGift::draw(sf::RenderWindow& window)
{
	sf::RectangleShape gift = getShape();

	// Set the bonus gift animation
	setAnimation();

	// Set the textureRect for the animation
	gift.setTextureRect(rectSourceTexture);

	// Set the bonus gift texture
	gift.setTexture(getGameObjectTexture());

	window.draw(gift);
}


//----------------- handleCollision ---------------------
// Handle collision with an object - for double dispach
//-------------------------------------------------------
void BonusGift::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}


//----------------- handleCollision ---------------
// Handle collision with a player.
// Let the player to pick u up and dispose from 
// the game.
//--------------------------------------------------
void BonusGift::handleCollision(Player& gameObject)
{
	m_isDisposed = true;
	gameObject.handleCollision((*this));
}


//---------------------- setAnimation -------------------------
//                    Set gift animation.
// Create an animation by using inrect object that cuts (by 
// constant size) the picture of the bonusGift.
//-------------------------------------------------------------
void BonusGift::setAnimation() {
	if (timeAnimation.getElapsedTime().asSeconds() > 0.2f)
	{
		if (rectSourceTexture.left >= GIFT_REC_SIZE)
		{
			rectSourceTexture.left = 0;
		}
		else {
			rectSourceTexture.left += BONUS_GIFT_WIDTH;
		}
		timeAnimation.restart();
	}
}


void BonusGift::handleDig(sf::Vector2f position) {}


void BonusGift::handleCollision(Enemy& gameObject) {}


void BonusGift::handleCollision(Ladder& gameObject) {}


void BonusGift::handleCollision(Block& gameObject){}


void BonusGift::handleCollision(Coin& gameObject) {}


void BonusGift::handleCollision(Pipe& gameObject) {}