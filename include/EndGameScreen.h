#pragma once
#include "SFML/Graphics.hpp"


//---------------------- class EndGameScreen -------------------
class EndGameScreen
{
public:

	// c-tor
	EndGameScreen();

	// d-tor
	virtual ~EndGameScreen() {}

	// Draw the 
	void draw(sf::RenderWindow& window, const bool wonTheGame);

	// Handles the button release in the end game screen
	void handleMouseButtonReleased(const sf::Vector2f& location,
		bool& showMenu);

	// Handles the situation the the mouse hovers the back button
	void handleHoverButton(const sf::Vector2f& location);

	// Sets the win screen data - displayed if the player wins
	void setWinScreen(sf::RenderWindow& window);

	// Sets the lose screen data - displayed if the player loses
	void setLostScreen(sf::RenderWindow& window);

	// Sets the plays win scores - life, stage and score
	void setWinGameData(const int score, const int stage,
		const int lifes);
	
private:

	// auxillary function to set the text needed for 
	// the endgame screen
	void setDataText(sf::Text& dataTxt, std::string str,
		const int info, const int pos_y);

	// Set the font of the end game screen
	void setFonts();

	// Set the title of the end game screen
	void setTitleText();

	// Set the back button of the end game screen
	void setBackButton();

	// RectangleShapes to hold and display the background
	// and the back to menu button.
	sf::RectangleShape m_background, backToMenuBtn;

	// To hold the needed texts that shold be displayed
	sf::Text titleTxt, scoreTxt, stageTxt, lifeTxt, backBtnTxt;

	// To hold info about the end game status 
	int finalScore = 0, finalLifeLeft = 0, finalStageNum = 0;
};
