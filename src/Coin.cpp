#include "Coin.h"
#include "Macros.h"

//------------------ c-tor ------------------------- 
Coin::Coin(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture)
	:StaticObject(height, width,
		sf::Vector2f(position.x + (width) * 0.5,
			position.y), texture)
{
	rectSourceTexture = sf::IntRect
	(0, 0, COIN_RECT_WIDTH, COIN_RECT_HEIGHT);
}


// d-tor
Coin::~Coin()
{}


//------------------- handleCollision --------------------- 
// Handle collistion with an object  - for double dispach
//---------------------------------------------------------
void Coin::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}


//------------------ handleCollision ------------------
// Handle collistion with player - let him collet you
//-----------------------------------------------------
void Coin::handleCollision(Player& gameObject)
{
	m_isDisposed = true;
	handleCollision((GameObject&)gameObject);
}


//----------------- draw ------------------- 
//       Draw the coin on the window
//------------------------------------------
void Coin::draw(sf::RenderWindow& window)
{
	sf::RectangleShape coin = getShape();

	// Set the animation of the coin
	setAnimation();

	// Set the textureRect for the animation
	coin.setTextureRect(rectSourceTexture);

	// Set the coin texture 
	coin.setTexture(getGameObjectTexture());

	window.draw(coin);
}


//----------------------- setAnimation ------------------------
//                   Set animation for coin.
//                  -------------------------
// Create an animation by using inrect object that cuts (by 
// constant size) the picture of the coin.
//-------------------------------------------------------------
void Coin::setAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.1f) 
	{
		if (rectSourceTexture.left >= COIN_REC_SIZE)
		{
			rectSourceTexture.left = 0;
		}
		else 
		{
			rectSourceTexture.left += COIN_WIDTH;
		}
		timeAnimation.restart();
	}
}


void Coin::handleDig(sf::Vector2f position) {}


void Coin::handleCollision(Enemy& gameObject) {}


void Coin::handleCollision(Ladder& gameObject) {}


void Coin::handleCollision(Block& gameObject) {}


void Coin::handleCollision(Coin& gameObject) {}


void Coin::handleCollision(Pipe& gameObject) {}


void Coin::handleCollision(EnemyBonusGift& gameObject) {}


void Coin::handleCollision(LifeBonusGift& gameObject) {}


void Coin::handleCollision(ScoreBonusGift& gameObject) {}


void Coin::handleCollision(TimeBonusGift& gameObject) {}