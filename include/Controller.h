#pragma once

//---------------- includes -----------------
#include "Board.h"
#include "fstream"
#include "Resources.h"
#include "Player.h"
#include "Macros.h"
#include "NormalEnemy.h"
#include "TrackingEnemy.h"
#include "ConstantEnemy.h"
#include "Menu.h"
#include "InstructionScreen.h"
#include "EndGameScreen.h"
#include "MoveObject.h"


//------------------ class Controller ------------------
class Controller
{
public:

	// c-tor
	Controller();

	// d-tor
	virtual ~Controller();

	// show  the screen
	void showScreen();

	// Clear the vector that hold the moveObjects 
	void clearVectorMoveObject();

	// Insert the player into the vector
	void setPlayerObject(const Player& item);

	// Insert a ConstantEnemy into the vector
	void setConstantEnemyObject(const ConstantEnemy& item);

	// Insert a NormalEnemy into the vector
	void setNormalEnemyObject(const NormalEnemy& item);
	
	// Insert a TrackingEnemy into the vector
	void setTrackingEnemyObject(const TrackingEnemy& item);
	
	// Return moveObject in index i.
	MoveObject& getMoveObject(const int&);

	// Return the size of the moveObject vector
	const int getMoveObjectsSize() const;

private:

	//Show menu screen
	void openMenu(sf::Event&);

	//Show instruction screen
	void openInstruction(sf::Event&);

	//Show end game screen
	void openEndGameScreen(sf::Event&);

	//Show main game screen.
	void runGame(sf::Clock&, float&, sf::Event&);

	// Return information about the player status in current stage
	void handlePlayerStatus();

	//Handle mouse button released.
	void handleMouseButtonReleased(const sf::Vector2f&);

	// Set the text fronts
	void setTextsFonts();

	// Load the next board
	void loadNextBoard();

	// Set the number from a file
	void setNumFromFile(int& num);

	// Intilize all data for start game state.
	void resetGameData();

	// Set the data of the game
	// (more info in function definition)
	void setGameDataWindow();

	// Draw the game data 
	void drawGameDataWindow();

	// Set the texts of the game
	void setTextData(sf::Text&);

	// Handle the time of the game
	void stageTimeHandler(sf::Clock&);

	// reload the map 
	void reloadMap();

	// draw the 
	void draw();

	// move Objects handle special events
	void handlePipeAndFall(const float&);

	// Turn on or off the soundTrack.
	void muteOrPlaySoundTrack();

	// the window
	sf::RenderWindow m_window;

	// the game data window 
	sf::RectangleShape m_gameDataWindow,
		mutePlayBtn;

	//Hold the map data of the game.
	std::ifstream m_boardFile;

	//reprasants screen states of the game.
	bool exitGame = false, 
		startGame = false, 
		showInstruction = false,
		showEndGameScreen = false,
		wonTheGame = false;

	// to hold the world map
	Board m_worldMap;

	//Screen menu of the game
	Menu m_menu;

	//Screen Instruction of how to play the game
	InstructionScreen m_instructScreen;

	//Screen at the end of how the game
	EndGameScreen m_endGameScreen;

	// hold data about the game
	int m_height = 0,
		m_width = 0,
		m_time = 0,
		m_intialStageTime = 0,
		m_stageNum = 0;

	// to display the gameObjectTextures score, health, stand and time
	sf::Text m_scoreTxt,
		m_healthTxt,
		m_stageTxt,
		m_timeTxt;

	// vector to hold the game enemies
	std::vector<std::unique_ptr<MoveObject>> m_moveObjects =
		std::vector<std::unique_ptr<MoveObject>>();
	
	Player* m_player = nullptr;

	sf::Clock gameMovementClock;
};
