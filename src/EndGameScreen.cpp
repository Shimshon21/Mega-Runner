#include "EndGameScreen.h"
#include "Macros.h"
#include "Resources.h"
#include <string>


//-------------------------- EndGameScreen --------------------------
// Display to the window the end game screen with all the needed
// data.
// the end game screen displays wether the plays won or lost the
// game and afterwards, displays the score, life, ...
//-------------------------------------------------------------------
EndGameScreen::EndGameScreen() :
	m_background({ WINDOW_WIDTH,WINDOW_HEIGHT }), 
backToMenuBtn(sf::Vector2f(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.1))
{
	Resources& r = Resources::instance();

	// Set the backgorund of the 
	m_background.setTexture(r.getWindowObjectTexture(DATA_MENU));

	//Back buttons.
	setBackButton();

	//Set title text.
	setTitleText();

	// Set fonts
	setFonts();
}


//------------------ setFonts -------------------
// Set the fonts of the end game screen 
//-----------------------------------------------
void EndGameScreen::setFonts()
{
	Resources& r = Resources::instance();

	backBtnTxt.setFont(*r.getArialfont());
	scoreTxt.setFont(*r.getArialfont());
	lifeTxt.setFont(*r.getArialfont());
	stageTxt.setFont(*r.getArialfont());
}


//--------------- setTitleText ----------------
// Set the title text of the end game screen
//---------------------------------------------
void EndGameScreen::setTitleText()
{
	Resources& r = Resources::instance();

	titleTxt.setFont(*r.getArialfont());
	titleTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.40,
		WINDOW_HEIGHT * 0.1));
	titleTxt.setCharacterSize(50);
}



//---------------------- setBackButton ------------------------
//       Set the back button in the exit game window
//--------------------------------------------------------------
void EndGameScreen::setBackButton()
{
	Resources& r = Resources::instance();

	//Set button.
	backToMenuBtn.setTexture(r.getWindowObjectTexture(BUTTON));
	backToMenuBtn.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.1,
		WINDOW_HEIGHT * 0.8));

	// Set back button
	std::string str = "Back";
	backBtnTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.82));
	backBtnTxt.setCharacterSize(50);
	backBtnTxt.setString(str);
}



//-------------------- draw ------------------------
// Draws the end game screen with the needed data.
// If the player wins the  
//--------------------------------------------------
void EndGameScreen::draw(sf::RenderWindow& window,
	const bool wonTheGame) 
{
	window.draw(m_background);
	window.draw(backToMenuBtn);
	window.draw(backBtnTxt);

	if (wonTheGame) {
		setWinScreen(window);
	}
	else {
		setLostScreen(window);
	}
}




//----------------- handleMouseButtonReleased ------------------
// Handle the event that the mouse button is clicked upon the 
// BACK button of the end gamescreen.
// ==> Go back to menu on button click.
//--------------------------------------------------------------
void EndGameScreen::handleMouseButtonReleased
(const sf::Vector2f& location, bool& showEndScreen)
{
	if (backToMenuBtn.getGlobalBounds().contains(location))
	{
		Resources::instance().buttonClickedSound();
		showEndScreen = false;
	}
}



//----------------------- handleHoverButton -----------------------
// Change button color on hover.
// handles the mouse that hovers the back button in the end game 
// screen. If the mouse hovers the back button, swich the color.
//-----------------------------------------------------------------
void EndGameScreen::handleHoverButton(const sf::Vector2f& location)
{
	if (backToMenuBtn.getGlobalBounds().contains(location))
	{
		// mouse hovers ==> change the color of the button
		backToMenuBtn.setTexture
		(Resources::instance().getWindowObjectTexture(BUTTON_HOVER));
	}
	else
	{
		// stay with the defualt color of the button
		backToMenuBtn.setTexture
		(Resources::instance().getWindowObjectTexture(BUTTON));
	}
}


//--------------------- setWinScreen ---------------------------
// Set the player win game, when the player complated all stages.
// Will be displays if the player wins.
//--------------------------------------------------------------
void EndGameScreen::setWinScreen(sf::RenderWindow& window)
{
	std::string str = "Congratulations\nYou Have Won!";
	titleTxt.setString(str);
	titleTxt.setStyle(sf::Text::Underlined);
	titleTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.40, WINDOW_HEIGHT * 0.1));
	titleTxt.setCharacterSize(50);

	// Set the score text with the needed width and height
	setDataText(scoreTxt, "Final Score: ",
		finalScore, WINDOW_HEIGHT * 0.3);

	// Set the stage text with the needed width and height
	setDataText(stageTxt, "Finish Stage: ",
		finalStageNum, WINDOW_HEIGHT * 0.4);

	// Set the life text with the needed width and height
	setDataText(lifeTxt, "Lifes left: ",
		finalLifeLeft, WINDOW_HEIGHT * 0.5);


	window.draw(titleTxt);        // draw the title text on the window
	window.draw(scoreTxt);		  // draw the score on the window
	window.draw(lifeTxt);	      // draw the life text on the window
	window.draw(stageTxt);		  // draw the stage text on the window
}


//------------ setLostScreen ----------------
// Set the player lose screen if no life left.
//--------------------------------------------
void EndGameScreen::setLostScreen(sf::RenderWindow& window) {
	titleTxt.setString(std::string("GAME OVER!"));
	titleTxt.setPosition(WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.4);
	titleTxt.setStyle(sf::Text::Underlined);
	titleTxt.setCharacterSize(100);
	window.draw(titleTxt);
}


//----------------- setWinGameData -----------------
//             Set the end win game data.
// Sets the data that needs to be displayed if the
// player wins the game.
//--------------------------------------------------
void EndGameScreen::setWinGameData(const int score,
	const int stage, const int lifes)
{
	finalScore = score;
	finalStageNum = stage;
	finalLifeLeft = lifes;
}


//------------------- setDataText --------------------
// Set the string, style, position and the charcter
// size of the text.
//----------------------------------------------------
void  EndGameScreen::setDataText(sf::Text &dataTxt,
	std::string str, const int info, const int pos_y) 
{		
	str += std::to_string(info);
	dataTxt.setString(str);
	dataTxt.setStyle(sf::Text::Bold);
	dataTxt.setPosition
	(sf::Vector2f(WINDOW_WIDTH * 0.30, pos_y));
	dataTxt.setCharacterSize(50);
}

