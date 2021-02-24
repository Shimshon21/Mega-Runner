#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
public:

	// c-tor
	Menu();

	// d-tor
	~Menu();

	// Draw the menu
	void draw(sf::RenderWindow&);

	// Handle user hover mouse above buttons.
	void handleHoverButton(const  sf::Vector2f&, sf::RenderWindow&);

	// Handle user clicks mouse on buttons.
	void handleClickButton(const  sf::Vector2f&,
		sf::RenderWindow&, bool&, bool&, bool&);

private:

	// The text of the button in the menu
	sf::Text startTxt, exitTxt, instructionTxt;

	// The buttons of the menu
	sf::RectangleShape menuWindow,
		startGameBtn,
		instructionBtn,
		exitGameBtn;

	//Set the menu screen.
	void setMenuScreen();

	//Set the button details by given params.
	void setButton(sf::RectangleShape&, sf::Text&,
		const std::string&,const int, const int);
};