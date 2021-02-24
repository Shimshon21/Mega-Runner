#include "MoveObject.h"
#include "Block.h"
#include "Ladder.h"
#include <cmath> 


// c-tor 
MoveObject::MoveObject(const sf::Vector2f& position, Board* world,
	const int height, const int width)
{
	m_world = world;
	m_moveObject.setSize(sf::Vector2f(width, height));
	m_moveObject.setPosition(position);
	m_oldPosition = m_moveObject.getPosition();
}

// d-tor
MoveObject::~MoveObject()
{}


//------------------ getPlayerPos ---------------------
// Return the players position in the world.
// The enmies use this information to track the player 
// and move smartly.
//-----------------------------------------------------
sf::Vector2f MoveObject::getPlayerPos() const
{
	return m_playerPos;
}


//------------------ setPlayerPos ---------------------
// Set the player position in the world.
// This data is always modified by the player 
// who does a move.
//-----------------------------------------------------
void MoveObject::setPlayerPos(const sf::Vector2f& position)
{
	m_playerPos = position;
}


//------------------ setScaleLeft ---------------------
// Set the player scale to left, according to scale
//-----------------------------------------------------
void MoveObject::setScaleLeft(const float& scale)
{
	m_moveObject.setScale(-scale, scale);
}


//----------------- setScaleRight ---------------------
// Set the player scale to right, according to scale
//-----------------------------------------------------
void MoveObject::setScaleRight(const float& scale)
{
	m_moveObject.setScale(scale, scale);
}


//----------------- handleInsideBlockEvent ---------------------
// Handle event when move object is inside block or stepping
// on invisible block.
//--------------------------------------------------------------
void MoveObject::handleInsideBlockEvent(Block& gameObject)
{
	if (gameObject.getShape().getFillColor() == sf::Color::Transparent) {

		gameObject.setSomeOneInside(true);

		m_moveObject.setPosition(gameObject.getPostition() +
			gameObject.getSize() / 2.f);

		m_oldPosition = m_moveObject.getPosition();

		insideBlock = true;

	}
	else if (insideBlock)
	{
		gameObject.setSomeOneInside(false);

		m_oldPosition = sf::Vector2f(m_oldPosition.x,
			gameObject.getPostition().y - gameObject.getSize().y);

		insideBlock = false;
	}
}


//----------------- handleCollision ------------------
// Handle collision with a block.
// Move the player\enemy back to the position before.
//----------------------------------------------------
void MoveObject::handleCollision(Block& gameObject)
{
	if (onPipe && !inHandlePipe)
	{
		m_moveObject.move(0, -1);
		return;
	}

	if ((mvUp || onLadder) && !mvDown)
	{
		handleCollisonBlockLadder(gameObject);
		return;
	}

	m_moveObject.setPosition(m_oldPosition);
	falling = false;

	if (!gameObject.isSomeoneInside() || insideBlock) {
		handleInsideBlockEvent(gameObject);
	}

	m_moveObject.setPosition(m_oldPosition);
	falling = false;
}


//--------------------- handleCollisonBlockLadder --------------------
//                Handle collison with block , on ladder.
//---------------------------------------------------------------------
void MoveObject::handleCollisonBlockLadder(Block& gameObject) 
{

	if (gameObject.getPostition().x < m_moveObject.getPosition().x)
	{
		m_moveObject.move(PUSH_BACK_BLOCK, 0);
	}
	else if (gameObject.getPostition().x > m_moveObject.getPosition().x)
	{

		m_moveObject.move(-PUSH_BACK_BLOCK, 0);
	}
	else
	{
		onLadder = false;
	}
}


//--------------------- setPosition --------------------
// Set the position of the object.
//------------------------------------------------------
void MoveObject::setPosition(const float& x, const float& y)
{
	m_moveObject.setPosition(x, y);
}


//------------------ isinsideBlock ------------------
//   Return if the moveable object is inside block
//---------------------------------------------------
bool MoveObject::isinsideBlock()
{
	return insideBlock;
}


//-------------------- getPosition -----------------------
// Return the moveObject position - the current object
// The current object can be an enemy or a player.
//--------------------------------------------------------
sf::Vector2f MoveObject::getPosition() const
{
	return (m_moveObject.getPosition());
}


//------------------------- legalMove -------------------------
// Check if the player did a legal move. If the moveObject did 
// an ilegal move, return false.
//-------------------------------------------------------------
bool MoveObject::legalMove(const sf::Vector2f& movement)
{
	auto temp_player = m_moveObject;
	temp_player.move(movement);

	if (temp_player.getPosition().x -
		temp_player.getSize().x / 1.5 < 0)
	{
		return false;
	}

	if (temp_player.getPosition().x +
		temp_player.getSize().x / 1.5 > WINDOW_WIDTH)
	{
		return false;
	}

	if (temp_player.getPosition().y +
		temp_player.getSize().x / 1.5 > WINDOW_HEIGHT)
	{
		return false;
	}

	if (temp_player.getPosition().y -
		temp_player.getSize().x / 1.5 < 0)
	{
		return false;
	}

	return true;
}


//----------------- handleCollision ------------------
// Handle collision with a Pipe.
// Move on the pipe and draw the player on pipe.
//----------------------------------------------------
void MoveObject::handleCollision(Pipe& gameObject)
{
	onPipe = true;

	if (!inHandlePipe)
	{
		falling = false;
	}
}


//----------------- getShape -------------------
//         Return the MoveObject shape
//----------------------------------------------
sf::RectangleShape MoveObject::getShape() const
{
	return m_moveObject;
}


//----------------- handleCollision ------------------
// Handle collision with a ladder.
// accept the player to move up and draw the picture 
// of the player on pipe.
//----------------------------------------------------
void MoveObject::handleCollision(Ladder& gameObject)
{
	auto tempMoveObj = m_moveObject;
	tempMoveObj.setOrigin(0, 0);

	if (abs(m_moveObject.getPosition().x -
		gameObject.getPostition().x) <
		gameObject.getSize().x &&
		tempMoveObj.getPosition().x >
		gameObject.getPostition().x)
	{
		if (mvUp || mvDown)
		{
			m_moveObject.setPosition
			({ gameObject.getPostition().x +
				(gameObject.getSize().x / 2.f),
				m_moveObject.getPosition().y });
		}
		onLadder = true;
		falling = false;

		if (insideBlock) 
		{
			m_moveObject.move(0, -m_moveObject.getSize().y);
			insideBlock = false;
		}
	}
}


//-------------- intializeEvents --------------
// intialize events that can accure in game
//---------------------------------------------
void MoveObject::intializeEvents()
{
	onLadder = false;
	onPipe = false;
	onTopOfLadder = false;
}


//----------------------- move -------------------------
// Move the move object in the world - virtual function 
//------------------------------------------------------
void MoveObject::move(const float&) {}

