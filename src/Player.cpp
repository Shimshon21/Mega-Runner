#include "Player.h"
#include <ctime>
#include "Macros.h"


int Player::m_score = 0;
int Player::m_lifes = PLAYER_LIVES;


// c-tor
Player::Player(const sf::Vector2f& position,
	Board* world, const int height, const int width)
	:MoveObject(position, world, height, width)
{
	// Set the players textures inrects - for the animation
	setTextureInrect();

	// Set the origin 
	m_moveObject.setOrigin(m_moveObject.getSize()/2.f );


	// Set the size and the texture of a new enemy apearing
	// in the game when the player picks up	an enemy gift.
	setEnemyGiftCharacteristics();
}

// d-tor
Player::~Player()
{}


//------------------------- draw -------------------------------
// Draw the player according to his location.
// Check what is the current status(i.e. if it's on ladder,
// pipe...) of the player and accordingly set the desired
// texture that should be displayed(draw) upon the window.
// After setting the needed texture, the function setAnimation 
// sets the needed animation.
//---------------------------------------------------------------
void Player::draw(sf::RenderWindow& window)
{
	//sf::Sprite playerPic;
	sf::RectangleShape playerPic = m_moveObject;
	sf::Vector2f position = m_moveObject.getPosition();
	Resources& r = Resources::instance();

	if (onLadder)
	{
		// Draw the player climbing
		if (mvUp || mvDown)
		{
			playerPic.setTexture
			(r.getGameObjectTexture(PLAYER_CLIMBING));
			playerPic.setTextureRect
			(rectSourceTextureClimbing);
		}
		else
		{
			playerPic.setTexture(r.getGameObjectTexture(PLAYER_CLIMB));
		}
	}
	else if (onPipe)
	{
		// Draw the player on pipe
		playerPic.setTexture(r.getGameObjectTexture(PLAYER_PIPE));
	}
	else if (falling || insideBlock)
	{
		// Draw the player falling
		playerPic.setTexture(r.getGameObjectTexture(PLYAER_FALLING));
		playerPic.setTextureRect(rectSourceTextureFalling);
	}
	else if (mvLeft || mvRight)
	{
		// Draw the player running
		playerPic.setTexture(r.getGameObjectTexture(PLAYER_RUNNING));
		playerPic.setTextureRect(rectSourceTextureRunning);
	}
	else if (digTheFloor)
	{
		// Draw the player digging the floor
		playerPic.setOrigin
		(m_moveObject.getSize().x - 0.8 * m_moveObject.getSize().x,
			m_moveObject.getOrigin().y);
		playerPic.setScale(2.3 * m_moveObject.getScale().x, 1);
		playerPic.setTextureRect(rectSourceTextureStrike);
		playerPic.setTexture((r.getGameObjectTexture(PLAYER_STRIKE)));
	}
	else
	{
		// Draw the player standing
		playerPic.setTextureRect(rectSourceTextureStanding);
		playerPic.setTexture((r.getGameObjectTexture(PLAYER_STAND_ANIME)));
	}
	setAnimation();


	window.draw(playerPic);
	if (insertEnemy) {
		window.draw(newEnemy);
	}
}


//---------------- handleCollision -----------------
// handle collision with an object in the world.
// This function is needed for double dispach.
//--------------------------------------------------
void Player::handleCollision(GameObject& gameObject)
{
	if (this == &gameObject) return;

	gameObject.handleCollision(*this);
}

 

//--------------------------- move -------------------------------
// Move the player object accodring to the current wanted move 
// the player just asked for.
// Note: The move will work if and only if the move is legal.
// The auxillary function legalMove checks if the current movement
// was legal or not.
//----------------------------------------------------------------
void Player::move(const float& deltaTime)
{
	handleTimeEvents();


	// Hold movement and check if it's legal
	auto movement = getMove(deltaTime);

	// if the movement was legal, move the player
	if (legalMove(movement))
	{
		m_oldPosition = m_moveObject.getPosition();
		m_moveObject.move(movement);
	}


	// intialize special events
	intializeEvents();

	// handle all the events
	handleEvents();
}


//------------------------ setAnimation -----------------------------
// This function cuts the texture to display the righ picture
// every second. Makes it look like an animation.
//-------------------------------------------------------------------
void Player::setAnimation()
{
	// climbing a ladder animation
	if (onLadder && (mvUp || mvDown))
		onLadderAnimation();
	
	// running animation
	if (mvLeft || mvRight)
		runningAnimation();

	// falling animaion
	if (falling || insideBlock)
		fallingAnimation();

	// digging the floor animaion
	if (digTheFloor)
		digAnimation();

	// staning animation 
	if (!digTheFloor && !falling && !(mvLeft || mvRight))
		standingAnimation();

	// player got enemy gift ==> insert enemy animation
	if (insertEnemy) 
		insertEnemyAnimation();
}


//------------------------ digFloor ----------------------------
// Check if the player wants to dig the floor from the ride
// side of the player or the left side of the player.
// X - the player wants to dig the right block located from  
//     the current position of the player.
// Y - the player wants to dig the left block located from  
//     the current position of the player.
//--------------------------------------------------------------
void Player::digFloor()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		m_moveObject.setScale(1, 1);
		digTheFloor = true;
		digRight = true;
		Resources::instance().strikeSound();

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (m_moveObject.getScale().x > 0)
			m_moveObject.scale(-1, 1);
		digTheFloor = true;
		digLeft = true;
		Resources::instance().strikeSound();
	}
}


//------------------------- handleEvents ------------------------
// Handle all the posible events in the game.
// i.e. block, ladder, coin ...
//---------------------------------------------------------------
void Player::handleEvents()
{
	// run over the tatic objects of the world and check 
	// and check collision
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


	for (int i = 0; i < m_world->getMoveObjectSize(); i++)
	{
		if (!insideBlock && !m_world->getMoveObject(i).isinsideBlock() && 
			checkCollision(m_moveObject.getGlobalBounds(),
			m_world->getMoveObject(i).getShape().getGlobalBounds()))
		{
			handleCollision(m_world->getMoveObject(i));
		}
	}
}


//--------------------- handlePipe -------------------------
// Handles the event that the player is on a pipe.
// we want the player to hold correctly the pipe.
//----------------------------------------------------------
void Player::handlePipe()
{
	inHandlePipe = true;	  // raise flag we in this func

	if (onPipe)               // enter only if on pipe
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



//--------------------------- getMove ------------------------------
//		      Return the next requested move of the player 
//           -----------------------------------------------
// Gets\Reads the wanted move from the player 
// and returns the requested movement.
//------------------------------------------------------------------
sf::Vector2f Player::getMove(const float& deltaTime)
{
	sf::Vector2f movement;
	mvUp = mvDown = mvRight = mvLeft = false;

	if (!falling)
	{
		if (!insideBlock)
		{
			// move up 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				&& onLadder)
			{
				mvUp = true;
				movement.x = 0;
				movement.y = -(PLAYER_SPEED * deltaTime);
			}

			// move down
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				mvDown = true;
				movement.x = 0;
				movement.y = (PLAYER_SPEED * deltaTime);
			}

			// move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& !digTheFloor)
			{
				mvLeft = true;
				setScaleLeft(m_moveObject.getScale().y);
				movement.x = -(PLAYER_SPEED * deltaTime);
				movement.y = 0;
			}

			// move right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
				&& !digTheFloor)
			{
				mvRight = true;
				setScaleRight(m_moveObject.getScale().y);
				movement.x = (PLAYER_SPEED * deltaTime);
				movement.y = 0;
			}

			// if the player is on ladder or pipe 
			// don't let him to dig 
			if (!onLadder && !onPipe)
			{
				digFloor();
			}
		}
	}
	
	// return the desired movement
	return movement;
}


//--------------------- setTextureInrect ------------------------
//         Auxillary function to set the texture intrects
//---------------------------------------------------------------
void Player::setTextureInrect()
{
	rectSourceTextureRunning = sf::IntRect(0, 0,
		PLAYER_RUNNING_WIDTH, PLAYER_RUNNING_HEIGHT);

	rectSourceTextureFalling = sf::IntRect(0, 0,
		PLAYER_FALLING_WIDTH, PLAYER_FALLING_HEIGHT);

	rectSourceTextureStrike = sf::IntRect(0, 0,
		PLAYER_STRIKE_WIDTH, PLAYER_STRIKE_HEIGHT);

	rectSourceTextureStanding = sf::IntRect(0, 0,
		PLAYER_STANDING_WIDTH, PLAYER_STANDING_HEIGHT);

	rectSourceTextureNewEnemy = sf::IntRect(0, 0,
		NEW_ENEMY_WIDTH, NEW_ENEMY_HEIGHT);

	rectSourceTextureClimbing = sf::IntRect(0, 0,
		PLAYER_CLIMBING_WIDTH, PLAYER_CLIMBING_HEIGHT);
}


//---------------------------------------------------
// Handle the situation of being on top of a ladder.
//---------------------------------------------------
void Player::handleOnTopOfLadder()
{
	// if player is on pipe or on ladder skip
	if (!onLadder && !onPipe)
	{
		m_oldPosition = m_moveObject.getPosition();      
		m_moveObject.move(0, 1);
		handleEvents();

		if (onLadder)
		{
			onLadder = false;
			onTopOfLadder = true;
		}

		// Set back to the prev position 
		m_moveObject.setPosition(m_oldPosition);
	}

	if (onTopOfLadder)
		handleDigOnladder();
}


//-------------------------- handleDigOnladder ------------------------
// The player handles the dig event when he is located on top of a 
// ladder.
// Because the ladder width and the block width are different, we have
// to use other distances for digging the block located from right or 
// left from the player.
//---------------------------------------------------------------------
void Player::handleDigOnladder()
{
	if (digLeft)
	{
		digRightFloor(sf::Vector2f(m_moveObject.getPosition().x - 50,
			m_moveObject.getPosition().y + 30));
		digLeft = false;
	}
	else if (digRight)
	{

		digRightFloor(sf::Vector2f(m_moveObject.getPosition().x + 50,
			m_moveObject.getPosition().y + 30));

		digRight = false;
	}
}


//----------------- handleCollision ------------------
// Handle collision with a coin.
// Collect the coin: add +1 to the amount of coins 
// collected and add to the score.
//----------------------------------------------------
void Player::handleCollision(Coin& gameObject)
{
	Resources::instance().collectCoinSound();
	m_coins++;
	m_score += m_world->getStageNum() * 2;
}


//---------------- handleCollision ------------------
// Handle collision with a gift.
// The player recives:
// 1 - +1 life,
// 2 - +20 score,
// 3 - more time
// 4 - new enemy in map
//---------------------------------------------------
void Player::handleCollision(EnemyBonusGift& gameObject)
{
	addEnemyTimer.restart();
	newEnemyTimer.restart();
	Resources::instance().collectEnemyGiftSound();
	insertEnemy = true;
	addNewEnemyPos = m_moveObject.getPosition();
}


//------------------- handleCollision -----------------------
// HandleCollision with a lifeBounus gift - collect the gift
//-----------------------------------------------------------
void Player::handleCollision(LifeBonusGift& gameObject)
{
	Resources::instance().collectGiftSound();
	m_lifes++;
}


//----------------------- handleCollision ------------------------
// HandleCollision with a ScoreBonusGift gift - collect the gift
//----------------------------------------------------------------
void Player::handleCollision(ScoreBonusGift& gameObject)
{
	Resources::instance().collectGiftSound();
	m_bonusGiftScore += 20;
	m_score += 20;
}


//----------------------- handleCollision ------------------------
// HandleCollision with a TimeBonusGift gift - collect the gift
//----------------------------------------------------------------
void Player::handleCollision(TimeBonusGift& gameObject)
{
	Resources::instance().collectGiftSound();
	if ((*m_time) != -1) {
		*m_time += 10;
	}
	else {
		m_bonusGiftScore += 20;
		m_score += 20;
	}
}


//---------------- handleCollision -------------------
// Handle collision with an enemy - get hit by enemy
// 1. Plays the sound of getting hit 
// 2. Updating that the player got hit
//----------------------------------------------------
void Player::handleCollision(Enemy& gameObject)
{
	Resources::instance().playerHitSound();
	hitEnemy = true;
}


//---------------- handleCollision ----------------
// Send to the base department
//-------------------------------------------------
void Player::handleCollision(Ladder& gameObject)
{
	MoveObject::handleCollision(gameObject);
}


//--------------- handleCollision ----------------
// Send to the base department
//------------------------------------------------
void Player::handleCollision(Pipe& gameObject)
{
	MoveObject::handleCollision(gameObject);
}


//----------------------- handleCollision ------------------------
// HandleCollision with a Block allow destroy left or right block
// for about 4 second.
//----------------------------------------------------------------
void Player::handleCollision(Block& gameObject)
{
	MoveObject::handleCollision(gameObject);

	if (digLeft) {
		if (m_moveObject.getPosition().x > 
			gameObject.getPostition().x &&
			(m_moveObject.getPosition().x <
				(gameObject.getPostition().x + gameObject.getSize().x))) 
		{
			digLeftFloor
			(sf::Vector2f(gameObject.getShape().getPosition().x - 1,
				gameObject.getShape().getPosition().y));
		}
		else {
			m_oldPosition.x += 25;
			m_moveObject.setPosition(m_oldPosition);
			digLeftFloor(sf::Vector2f(gameObject.getShape().getPosition().x,
				gameObject.getShape().getPosition().y));
		}
		digLeft = false;
	}

	else if (digRight) {
		digRightFloor(sf::Vector2f(gameObject.getShape().getPosition().x +
			gameObject.getShape().getSize().x,
			gameObject.getShape().getPosition().y));
		digRight = false;
	}
}


//------------------------ digLeftFloor -------------------------
// The player digs the floor.
// the function runs over the objects and checks 
//---------------------------------------------------------------
void Player::digLeftFloor(sf::Vector2f position)
{
	for (int i = 0; i < m_world->getStaticObjectsSize(); i++)
	{
		m_world->getStaticObject(i).handleDig( position);
	}
}


//---------------------- digRightFloor -------------------------
// The player digs the floor.
// the function runs over the objects and checks 
//--------------------------------------------------------------
void Player::digRightFloor(sf::Vector2f position)
{
	for (int i = 0; i < m_world->getStaticObjectsSize(); i++)
	{
		m_world->getStaticObject(i).handleDig(position);
	}
}


//---------------------- onLadderAnimation ----------------------
// Create an animation by using inrect object that cuts the 
// picture of the player being on ladder by constant size.
//---------------------------------------------------------------
void Player::onLadderAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.08f)
	{
		if (rectSourceTextureClimbing.left >=
			PLAYER_CLIMBING_REC_SIZE) {
			rectSourceTextureClimbing.left = 0;
		}
		else
		{
			rectSourceTextureClimbing.left += PLAYER_CLIMBING_WIDTH;
		}
		timeAnimation.restart();
	}
}


//---------------------- runningAnimation ------------------------
// Create an animation by using inrect object that cuts the 
// picture of the player running by constant size.
//----------------------------------------------------------------
void Player::runningAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.05f)
	{
		if (rectSourceTextureRunning.left >=
			PLAYER_RUNNING_REC_SIZE) {
			rectSourceTextureRunning.left = 0;
		}
		else
		{
			rectSourceTextureRunning.left += PLAYER_RUNNING_WIDTH;
		}
		timeAnimation.restart();
	}
}


//----------------------- fallingAnimation -----------------------
// Create an animation by using inrect object that cuts the 
// picture of the player falling by constant size.
//---------------------------------------------------------------
void Player::fallingAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.1f)
	{
		if (rectSourceTextureFalling.left >=
			PLAYER_FALLINING_REC_SIZE) {
			rectSourceTextureFalling.left = 0;
		}
		else
		{
			rectSourceTextureFalling.left += 43;
		}
		timeAnimation.restart();
	}
}


//----------------------- digAnimation ---------------------
// Create an animation by using inrect object that cuts the 
// picture of the player being on ladder by constant size.
//----------------------------------------------------------
void Player::digAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.05f)
	{
		if (rectSourceTextureStrike.left >=
			PLAYER_STRIKE_REC_SIZE) {
			rectSourceTextureStrike.left = 0;
			digTheFloor = false;
		}
		else
		{
			rectSourceTextureStrike.left += 137;
		}
		timeAnimation.restart();
	}
}



//----------------------- standingAnimation -------------------------
// Create an animation by using inrect object that cuts (by constant 
// size) the picture of the player being on ladder. 
//-------------------------------------------------------------------
void Player::standingAnimation()
{
	if (timeAnimation.getElapsedTime().asSeconds() > 0.15f)
	{
		if (rectSourceTextureStanding.left >=
			PLAYER_STANDING_REC_SIZE) {
			rectSourceTextureStanding.left = 0;
		}
		else
		{
			rectSourceTextureStanding.left += PLAYER_STANDING_WIDTH;
		}
		timeAnimation.restart();
	}
}


//--------------------- insertEnemyAnimation ------------------------
// Create an animation by using inrect object that cuts (by constant
// size) the picture of the player staning on the floor.
//-------------------------------------------------------------------
void Player::insertEnemyAnimation()
{
	if (newEnemyTimer.getElapsedTime().asSeconds() > 0.25f)
	{

		newEnemy.setPosition(sf::Vector2f
		({ addNewEnemyPos.x - 40 , addNewEnemyPos.y - 80 }));
		newEnemy.setFillColor(sf::Color::White);
		newEnemy.setTextureRect(rectSourceTextureNewEnemy);
		rectSourceTextureNewEnemy.left += 57;
		newEnemyTimer.restart();
	}
}


//---------------- setEnemyGiftCharacteristics ---------------------
// Set the size and the texture of a new enemy apearing in the game
// when the player collects an enemy gift.
//------------------------------------------------------------------
void Player::setEnemyGiftCharacteristics()
{
	// Set enemy gift texture.
	newEnemy.setSize(m_moveObject.getSize() * 1.5f);

	// Set the texture of enemy gift
	newEnemy.setTexture(Resources::instance()
		.getGameObjectTexture(ENEMY_GIFT));
}


//----------------- setTime -----------------
//Set pointer of the time of the game.
//--------------------------------------------
void Player::setTime(int* time)
{
	m_time = time;
}


//---------------------- handleTimeEvents ----------------------
// Handle time events.
// Handle the event that the player got an enemy gift.
// If the enemy got an enemy gift, give him 3 seconds to move
// away before the enemy pops out.
//--------------------------------------------------------------
void Player::handleTimeEvents()
{
	if (insertEnemy)
	{
		if (addEnemyTimer.getElapsedTime().asSeconds() > 3.f )
		{
			newEnemy.setFillColor(sf::Color::Transparent);
			
			insertEnemy = false;
			m_world->insertNewEnemy({ addNewEnemyPos.x,
				addNewEnemyPos.y - PUSH_BACK_BLOCK });

			rectSourceTextureNewEnemy.left = 0;
		}
	}
}


//----------------- getScore -----------------
//       Return the score of the player.
//--------------------------------------------
int Player::getScore() const
{
	return m_score;
}


//--------------- isPlayerGotHit --------------
//    Return if the player got hit by enemy
//---------------------------------------------
bool Player::isPlayerGotHit() const
{
	return hitEnemy;
}


//----------------- resetScore -----------------
//              Rest score to zero
//----------------------------------------------
void Player::resetScore() {
	m_score = 0;
}


//----------------- stageBonusAddScore -----------------
//                Return the stage bonus
//------------------------------------------------------
void Player::stageBonusAddScore()
{
	m_score += m_world->getStageNum() * 50;
}


//----------------- decreaseStageScore -----------------
//            Decrease the score of the player.
//------------------------------------------------------
void Player::decreaseStageScore()
{
	m_score -= (m_coins * (m_world->getStageNum() * 2)
		+ m_bonusGiftScore);
	m_bonusGiftScore = 0;
	m_coins = 0;
}


//----------------- getLifes -----------------
//       Return the lifes of the player.
//--------------------------------------------
int Player::getLifes() const
{
	return m_lifes;
}


//----------------- resetCoins -----------------
//      Rest the amount of coins to zero.
//----------------------------------------------
void Player::resetCoins()
{
	m_coins = 0;
}


//------------------- getCoins --------------------
// Return the amount of coins the player collected
//-------------------------------------------------
int Player::getCoins() const
{
	return m_coins;
}


//------------------- resetLife -------------------
// Increase the total amount of life of the player.
//-------------------------------------------------
void Player::resetLife()
{
	m_lifes = PLAYER_LIVES;
}


//----------------- increaseLife ------------------
// Increase the total amount of life of the player.
//-------------------------------------------------
void Player::increaseLife()
{
	m_lifes++;
}


//----------------- decreaseLife ------------------
// Decrease the total amount of life of the player.
//-------------------------------------------------
void Player::decLifeByOne()
{
	m_lifes--;
}


//------------------------- handleFall -------------------------
// Handle the fall of the player.
// Assume that the player is falling.
// Check what is the current position of the player.
// If the current position of the player is not in 
// the air ==> don't fall and exit.
// If the player is falling ==> move the player downwards.
//--------------------------------------------------------------
void Player::handleFall(
	const float& deltaTime)
{
	if (!onPipe && !onLadder)		
	{
		// assume the player is falling
		falling = true;            


		// Handle the event that the player is on top of ladder. 
		// If the player on top of ladder ==> don't fall don't fall.
		handleOnTopOfLadder();     

		if (!onTopOfLadder)
		{
			m_oldPosition = m_moveObject.getPosition();
			if (falling)
			{
				m_moveObject.move(0, PLAYER_FALL_SPEED * deltaTime);

				// after the slight movement downwards the if the 
				// move object collides with block, pipe, ladder... 
				handleEvents();
				if (!falling)
				{
					m_moveObject.setPosition(m_oldPosition);
				}
			}
		}
	}
}

void Player::handleCollision(Player& gameObject) {}