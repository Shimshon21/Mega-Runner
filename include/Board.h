#pragma once

//-------------- include section ----------------
#include <SFML/Graphics.hpp>
#include <memory>
#include <StaticObject.h>
#include "Resources.h"
#include <fstream>
#include "Block.h"
#include "Ladder.h"
#include "Pipe.h"
#include "Coin.h"
#include "BonusGift.h"
#include "Macros.h"
#include "ConstantEnemy.h"
#include "NormalEnemy.h"
#include "TrackingEnemy.h"
#include "Player.h"
class Controller;


//------------------ class Board --------------------
class Board
{
public:

	// c-tor
	Board(Controller*);

	// d-tor
	~Board();

	// Draw the board
	void draw(sf::RenderWindow&);

	// Set a new board
	void intializeNewBoard(const int&, const int&, std::ifstream&);

	// Set the size of the board 
	void setBoardSize(const int&, const int&);

	// Return the static object
	StaticObject& getStaticObject(const int&) const;

	// Return the move object
	MoveObject& getMoveObject(const int&) const;

	// Get size of moveObject vector.
	int getMoveObjectSize();

	// count the amount of coins
	const unsigned int getCountCoins() const;

	// reload the map
	void reloadBoard();

	// Get the amount of object in our world
	int getStaticObjectsSize() const;

	// Remove the static object from the world
	void removeStaticObject(const int&);

	// Return the stage num
	int getStageNum() const;

	// Rest the stage number
	void resetStageNum();

	// Set the enemy vector.
	void setEnemiesIntoVector(const int&, const sf::Vector2f&);

	// Push new Enemy into moveObject vector.
	void insertNewEnemy(const sf::Vector2f&);

	// Return the players index in the vector that 
	// hold all the move objects
	int getPlayerIndex() const;

private:

	// auxillary functio to set all the game objects
	void setBoardGameObjects();

	// set the game objects into the vector in right place
	void setGameObjectsVector(const int&,
		const int&, const sf::Vector2f&);

	// Set a gift object - divides the gifts 
	void setGiftIntoVector(const int&, const int&,
		const sf::Vector2f&, sf::Texture*);

	// set the background of the game
	void setBackground();

	// set the intial board
	void setIntialBoard(std::ifstream& boardFile);

	// to hold the data 
	int m_height = 0, m_width = 0;
	unsigned int fileStartMapPos = 0,
		countCoins = 0, m_stage = 0;

	// to hold the background texture
	sf::Texture m_backGroundTexure;

	// to hold the back ground
	sf::RectangleShape m_backgound;

	// vectore to hold the game objects
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects =
		std::vector<std::unique_ptr<StaticObject>>();

	// to hold the player beg position 
	sf::Vector2f m_playerBegPos;

	// to hold all the needed gameObjectTextures to draw the world
	std::vector<sf::Texture> m_gameObjectTextures;

	// To hold the map data
	std::vector <std::vector<char>> m_intlizeMap;

	// to hold the player index in the vector that
	// hold all the moveObjects
	int m_playerIndex = 0;

	Controller* m_controller;
};