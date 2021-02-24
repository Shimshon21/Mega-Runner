#pragma once
#include "SFML/Graphics.hpp"


//-------------------- class InstructionScreen -----------------
class InstructionScreen
{
public:

	// c-tor
	InstructionScreen();

	// d-tor
	virtual ~InstructionScreen();

	// Handles the event that the button is released
	void handleMouseButtonReleased(const sf::Vector2f& location,
		bool& showInstruction);

	// Handle the event that the mouse howers the back button
	void handleHoverButton(const sf::Vector2f& location);
	
	// Draw the instruction screen on the window
	void draw(sf::RenderWindow& window);

	// Set the needed data that should be displayed
	void setInstructionScreen();

	// Sets the disered distance between the latters
	// and the gameObjectTextures 
	void setItemDesc(sf::RectangleShape& gameObject,
		const int textureNum, sf::Text& objectDescText, 
		const std::string& objectDescStr, const int pos_x,
		const int pos_y);


private:

	// To hold the gameObjectTextures of the player,
	// enemy, coin ...
	sf::RectangleShape
		m_background,
		backBtn,
		player,
		hit,
		enemy,
		coin,
		gift;

	// To hold the text that should be displayed
	sf::Text
		backBtnTxt,
		playerTxt,
		gameIconsTxt,
		gameDescTitleTxt,
		gameDescTxt,
		enemyTxt,
		coinTxt,
		giftTxt;


	// Sets the texts titles
	void setTextTitles(sf::Text& titleTxt, std::string str,
		const int pos_x, const int pos_y);
};