#include "Enemy.h"
#include "Board.h"


// c-tor
Enemy::Enemy(const sf::Vector2f& position,
	Board* world, const int height, const int width)
	: MoveObject({ position.x,position.y - PUSH_BACK_BLOCK },
		world, height, width)
{
	m_moveObject.setTexture(
		Resources::instance().getGameObjectTexture(ENEMY_STAND));

	m_moveObject.setOrigin(m_moveObject.getSize() / (float)2);

	setTextureInrect();
}

//d-tor
Enemy::~Enemy()
{}


// Move the enemy - virtual function 
void Enemy::move(const float&) {}



//--------------------------- draw -----------------------------
// Draw the enemy object according to his location.
// Check what is the current status(i.e. if it's on ladder,
// pipe...) of the enemy and accordingly set the texture that
// should be displayed(draw) upon the window.
// After setting the needed texture, the function setAnimation 
// sets the needed animation.
//--------------------------------------------------------------
void Enemy::draw(sf::RenderWindow& window)
{
	//sf::Sprite playerPic;
	sf::RectangleShape enemyPic = m_moveObject;

	Resources& r = Resources::instance();

	if (onLadder)
	{
		// Draw the player climbing
		if (mvUp || mvDown)
		{
			// Draw the enemy climbing the ladder with the animation
			enemyPic.setTexture(r.getGameObjectTexture(ENEMY_CLIMBING));
			enemyPic.setTextureRect(recSourceTextureClimbing);
		}
		else
		{
			// Draw the enemy just on hold on the ladder  
			enemyPic.setTexture(r.getGameObjectTexture(ENEMY_CLIMB));
			enemyPic.setTextureRect(recSourceTextureClimb);
		}
	}
	else if (onPipe)
	{
		// Draw the player on pipe
		enemyPic.setTexture(r.getGameObjectTexture(ENEMY_PIPE));
		enemyPic.setTextureRect(recSourceTexturePipe);
	}
	else if (falling)
	{
		// Draw the player falling
		enemyPic.setTexture(r.getGameObjectTexture(ENEMY_FALL));
	}
	else if (mvLeft || mvRight)
	{
		// Draw the player running
		enemyPic.setTexture(r.getGameObjectTexture(ENEMY_RUNNING));
		enemyPic.setTextureRect(rectSourceTextureRunning);

	}
	else
	{
		// Draw the player standing
		enemyPic.setTexture(r.getGameObjectTexture(ENEMY_STAND));
	}

	// set animation
	setAnimation();

	// Draw enemy on window
	window.draw(enemyPic);
}


//----------------- handleCollision --------------------
// Handle collision with an object - needed for double
// dispach
//------------------------------------------------------
void Enemy::handleCollision(GameObject& gameObject)
{
	if (this == &gameObject) return;

	gameObject.handleCollision(*this);
}


//------------------------- handleEvents ------------------------
// Handle all the posible events in the game.
// i.e. block, ladder, coin ...
//---------------------------------------------------------------
void Enemy::handleEvents()
{
	for (int i = 0; i < m_world->getStaticObjectsSize(); i++)
	{
		if (checkCollision(m_moveObject.getGlobalBounds(),
			m_world->getStaticObject(i).
			getShape().getGlobalBounds()))
		{
			handleCollision(m_world->getStaticObject(i));
			if (m_world->getStaticObject(i).isDisposed())
				m_world->removeStaticObject(i);
		}
	}
}


//------------------------ setAnimation -----------------------------
// This function cuts the texture to display the righ picture
// every second. Makes it look like an animation.
//-------------------------------------------------------------------
void Enemy::setAnimation()
{
	// moving right or left animation
	if ((mvLeft || mvRight) && !onLadder && !onPipe)
		runningAnimation();

	// climbing ladder animation
	if (onLadder && (mvUp || mvDown))
		climbingAnimation();
}


//------------------- setTextureInrect --------------------
//      Auxillary function to set the texture inrects
//---------------------------------------------------------
void Enemy::setTextureInrect()
{
	rectSourceTextureRunning = sf::IntRect(0, 0,
		ENEMY_RUNNING_WIDTH, ENEMY_RUNNING_HEIGHT);

	recSourceTextureClimbing = sf::IntRect(0, 0,
		ENEMY_CLIMBING_WIDTH, ENEMY_CLIMBING_HEIGHT);

	recSourceTexturePipe = sf::IntRect(0, 0,
		ENEMY_PIPE_WIDTH, ENEMY_PIPE_HEIGHT);

	recSourceTextureClimb = sf::IntRect(0, 0,
		ENEMY_CLIMB_WIDTH, ENEMY_CLIMB_HEIGHT);
}


//----------------------- runningAnimation -------------------------
// Create an animation by using inrect object that cuts (by constant
// size.) the picture of the enemy running.
// The animation is played only if the enemy moves left or right.
//------------------------------------------------------------------
void Enemy::runningAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.03f)
	{
		if (rectSourceTextureRunning.left >=
			ENEMY_RUNNING_REC_SIZE) {
			rectSourceTextureRunning.left = 0;
		}
		else
		{
			rectSourceTextureRunning.left += ENEMY_RUNNING_WIDTH;
		}
		timeAnimation.restart();
	}
}


//----------------------- climbingAnimation -------------------------
// Create an animation by using inrect object that cuts (by constant
// size) the picture of the enemy climbing a ladder.
// The animation is played only if the enemy moves up or down.
//------------------------------------------------------------------
void Enemy::climbingAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.08f)
	{
		if (recSourceTextureClimbing.left >=
			ENEMY_CLIMBING_REC_SIZE) {
			recSourceTextureClimbing.left = 0;
		}
		else
		{
			recSourceTextureClimbing.left += ENEMY_CLIMBING_WIDTH;
		}
		timeAnimation.restart();
	}
}


//--------------- handleOnTopOfLadder ---------------
// Handle the situation of being on top of a ladder.
//---------------------------------------------------
void Enemy::handleOnTopOfLadder()
{
	// if player is on pipe or on ladder skip
	if (!onLadder && !onPipe)
	{
		m_oldPosition = m_moveObject.getPosition();  
		m_moveObject.move(0, 1);
		handleEvents();

		// check if after a short movement
		// the enemy in on ladder.
		if (onLadder)
		{
			onLadder = false;
			onTopOfLadder = true;
		}
		m_moveObject.setPosition(m_oldPosition);
	}
}


//--------------------- handlePipe -------------------------
// Handles the event that the enemy is on a pipe.
// We want the enemy to hold the pipe correctly.
//----------------------------------------------------------
void Enemy::handlePipe()
{
	inHandlePipe = true;

	if (onPipe)
	{
		while (onPipe)
		{
			onPipe = false;
			m_oldPosition = m_moveObject.getPosition();
			m_moveObject.move(0, PIPE_FALL);
			handleEvents();
			if (!falling) break;
		}
		m_moveObject.setPosition(m_oldPosition);
		onPipe = true;
		inHandlePipe = false;
	}
}


//---------------- handleCollision -------------------
// Handle collision with player - kill him 
//----------------------------------------------------
void Enemy::handleCollision(Player& gameObject) {
	gameObject.handleCollision(*this);
}


//----------------- handleCollision ------------------
// Send to the base department
//----------------------------------------------------
void Enemy::handleCollision(Ladder& gameObject)
{
	MoveObject::handleCollision(gameObject);
}


//----------------- handleCollision ------------------
// Send to the base department
//----------------------------------------------------
void Enemy::handleCollision(Pipe& gameObject)
{
	MoveObject::handleCollision(gameObject);
}


//----------------- handleCollision ------------------
// Send to the base department
//----------------------------------------------------
void Enemy::handleCollision(Block& gameObject)
{
	MoveObject::handleCollision(gameObject);
}


//----------------- handleFall --------------------
// Handle the fall of the enemy.
// Assume that the enemy is falling.
// Check what is the current position of the enemy.
// If the current position of the enemy is not in 
// the air ==> don't fall and exit.
// If the enemy is falling ==> move the enemy
// and draw the falling animation.
//-------------------------------------------------
void Enemy::handleFall(
	const float& deltaTime)
{
	if (!onPipe && !onLadder)
	{
		falling = true;
		handleOnTopOfLadder();

		if (!onTopOfLadder)
		{
			m_oldPosition = m_moveObject.getPosition();
			if (falling)
			{
				m_moveObject.move(0, PLAYER_FALL_SPEED * deltaTime);
				handleEvents();
				if (!falling)
				{
					m_moveObject.setPosition(m_oldPosition);
				}
			}
		}
	}
}


void Enemy::handleCollision(Enemy& gameObject) {}


void Enemy::handleCollision(Coin& gameObject) {}


void Enemy::handleCollision(EnemyBonusGift& gameObject) {}


void Enemy::handleCollision(LifeBonusGift& gameObject) {}


void Enemy::handleCollision(ScoreBonusGift& gameObject) {}


void Enemy::handleCollision(TimeBonusGift& gameObject) {}
