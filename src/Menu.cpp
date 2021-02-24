#include "Menu.h"
#include "Macros.h"
#include "Resources.h"


// c-tor
Menu::Menu() :
	menuWindow(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)),
	startGameBtn(sf::Vector2f(WINDOW_WIDTH * 0.5,
		WINDOW_HEIGHT * 0.1)),
	exitGameBtn(sf::Vector2f(WINDOW_WIDTH * 0.5,
		WINDOW_HEIGHT * 0.1)),
	instructionBtn(sf::Vector2f(WINDOW_WIDTH * 0.5,
		WINDOW_HEIGHT * 0.1))
{
	Resources& r = Resources::instance();

	// Set the screen menu
	setMenuScreen();
}


// d-tor
Menu::~Menu() {}


//----------------------- draw ------------------------
// Draw the menu screen with all the defined features.
//------------------------------------------------------
void Menu::draw(sf::RenderWindow& window)
{
	// Draw the menw window 
	window.draw(menuWindow);

	// Draw the start button
	window.draw(startGameBtn);

	// Draw the instruction button
	window.draw(instructionBtn);

	// Draw the exit button
	window.draw(exitGameBtn);

	// Draws the start text upon the start button
	window.draw(startTxt);

	// Draws the exit text upon the start button
	window.draw(exitTxt);

	// Draws the instructions text upon the start button
	window.draw(instructionTxt);
}


//---------------------- handleHoverButton ---------------------
// Handle mouse hovering on buttons.
// Checks if the current location of the mouse is hovering one
// of the menu button. 
// If the mouse is hovering the the button, Then new texture
// is setted instead of the prevous one.
// The new texture is displayed as long as the mouse is over
// the button.
//--------------------------------------------------------------
void Menu::handleHoverButton(const sf::Vector2f& location,
	sf::RenderWindow& window)
{
	// Handle the event that the mouse is hovering the Start button
	if (startGameBtn.getGlobalBounds().contains(location))
		startGameBtn.setTexture(Resources::instance()
			.getWindowObjectTexture(BUTTON_HOVER));
	else 
		startGameBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON));

	// Handle the event that the mouse is hovering the Exit button
	if (exitGameBtn.getGlobalBounds().contains(location)) 
		exitGameBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON_HOVER));
	else
		exitGameBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON));

	// Handle the event that the mouse is hovering 
	// the Instructions button
	if (instructionBtn.getGlobalBounds().contains(location)) 
		instructionBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON_HOVER));
	else
		instructionBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON));
}


//---------------- handleClickButton ------------------
// Handle mouse clicking on the buttons:
// start:Start the game.
// instructions: show explaination of the game.
// exit: Exit from the game.
//-----------------------------------------------------
void Menu::handleClickButton(const sf::Vector2f& location, 
	sf::RenderWindow& window, bool& exitGame, bool& startGame,
	bool& showInstruction)
{
	// Handle the event the mouse click is released upon the 
	// Start button
	if (startGameBtn.getGlobalBounds().contains(location))
	{
		startGame = true;
		Resources::instance().playSoundTrack();
	}

	// Handle the event the mouse click is released upon the 
	// Exit button
	else if (exitGameBtn.getGlobalBounds().contains(location))
	{
		exitGame = true;
	}

	// Handle the event the mouse click is released upon the 
	// Instructions button
	else if (instructionBtn.getGlobalBounds().contains(location)) 
	{
		showInstruction = true;
	}


	// Play the sound of pressing a button
	if (startGame || exitGame || showInstruction) 
	{
		Resources::instance().buttonClickedSound();
	}
}


//--------------------- setMenuScreen ------------------
// Set the menu screen info and elements.
//------------------------------------------------------
void Menu::setMenuScreen()
{
	Resources& r = Resources::instance();

	// Set the texture of the menu window
	menuWindow.setTexture(Resources::instance().
		getWindowObjectTexture(DATA_MENU));

	// Set the position of the of Start game button
	startGameBtn.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.2));

	// Set the position of the instructions button
	instructionBtn.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.4));

	// Set the position of the Exit button upon the window
	exitGameBtn.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.25, WINDOW_HEIGHT * 0.6));


	// Set the Start game button with the sended args
	setButton(startGameBtn, startTxt, "Start",
		WINDOW_WIDTH * 0.46, WINDOW_HEIGHT * 0.21);

	// Set the Instructions button with the sended args
	setButton(instructionBtn, instructionTxt, "Instructions",
		WINDOW_WIDTH * 0.43, WINDOW_HEIGHT * 0.41);

	// Set the Exit button with the sended args
	setButton(exitGameBtn, exitTxt, "Exit",
		WINDOW_WIDTH * 0.47, WINDOW_HEIGHT * 0.61);
}


//--------------------- setButton ------------------
// Set the button elemnts according given params.
//--------------------------------------------------
void Menu::setButton(sf::RectangleShape &buttonShape,
	sf::Text &buttonText,const std::string &buttonStr,
	const int width, const int height)
{
	// Set the texture if the button
	buttonShape.setTexture(Resources::instance().
		getWindowObjectTexture(BUTTON));

	// Set the position of the button  
	// Depending on the width and height
	buttonText.setPosition(sf::Vector2f(width, height));

	// Set the font - the fond is Arial font 
	buttonText.setFont(*Resources::instance().getArialfont());
	
	// Set the string that should be displayed upon the button
	buttonText.setString(buttonStr);

	// Set the charcter size of the string seted
	buttonText.setCharacterSize(50);

	// Set the color
	buttonText.setColor(sf::Color::White);
}
