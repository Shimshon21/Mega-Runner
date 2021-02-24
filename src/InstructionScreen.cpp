#include "InstructionScreen.h"
#include "Macros.h"
#include "Resources.h"


//----------------------------- constractor -----------------------------
// Sets the The desired size of the objects that should be 
// displayed if the user enters the instructions from the menu.
// The c-tor uses the help of the auxillary function 
// setInstructionScreen that sets the instructs texts.
//-----------------------------------------------------------------------
InstructionScreen::InstructionScreen():
	m_background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)),
	backBtn(sf::Vector2f(WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.1)),
	player(sf::Vector2f(WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.05)),
	enemy(sf::Vector2f(WINDOW_WIDTH * 0.05, WINDOW_HEIGHT * 0.05)),
	coin(sf::Vector2f(WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.03)),
	gift(sf::Vector2f(WINDOW_WIDTH * 0.03, WINDOW_HEIGHT * 0.03))
{
	
	// Set the coins Rect
	sf::IntRect rect = sf::IntRect(0, 0, COIN_RECT_WIDTH,
		COIN_RECT_HEIGHT);
	coin.setTextureRect(rect);

	// Set the gifts Rect
	rect = sf::IntRect(GIFT_REC_SIZE , 0, GIFT_WIDTH, GIFT_HEIGHT);
	gift.setTextureRect(rect);

	// Set the needed data that should be
	// displayed upon the instruction screen
	setInstructionScreen();
}


// d-tor
InstructionScreen::~InstructionScreen() {}



//-------------------- handleMouseButtonReleased --------------------
//        Handles the event that the button is released
//--------------------------------------------------------------
void InstructionScreen::handleMouseButtonReleased
(const sf::Vector2f& location,bool & showInstruction) 
{
	if (backBtn.getGlobalBounds().contains(location))
	{
		Resources::instance().buttonClickedSound();
		showInstruction = false;
	}
}


//---------------------- handleHoverButton ----------------------------
//       Handle the event that the mouse howers the back button
//---------------------------------------------------------------------
void InstructionScreen::handleHoverButton(const sf::Vector2f& location)
{
	if (backBtn.getGlobalBounds().contains(location))
	{
		backBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON_HOVER));
	}
	else
	{
		backBtn.setTexture(Resources::instance().
			getWindowObjectTexture(BUTTON));
	}
}


//------------------------ draw ---------------------------
//    Draw the instruction screen on the window
//---------------------------------------------------------
void InstructionScreen::draw(sf::RenderWindow& window)
{

	// Draw the background
	window.draw(m_background);

	// Draw the icons
	window.draw(gameIconsTxt);
	window.draw(gameDescTitleTxt);
	window.draw(gameDescTxt);

	// Draw the button of the instruction scree 
	// (the back to menu button)
	window.draw(backBtn);
	window.draw(backBtnTxt);

	// Draw the player icon and then the player text
	window.draw(player);
	window.draw(playerTxt);

	// Draw the enemy icon and then the enemy text
	window.draw(enemy);
	window.draw(enemyTxt);

	// Draw the coin icon and then the coin text
	window.draw(coin);
	window.draw(coinTxt);
	
	// Draw the gift icon and then the gift text
	window.draw(gift);
	window.draw(giftTxt);
}


//---------------------- setInstructionScreen -----------------------
// Set the needed data that should be displayed upon the instruction
// screen
//-------------------------------------------------------------------
void InstructionScreen::setInstructionScreen() 
{
	Resources& r = Resources::instance();

	// Set the background texture
	m_background.setTexture(r.getWindowObjectTexture(DATA_MENU));

	//Set button.
	backBtn.setTexture(r.getWindowObjectTexture(BUTTON));
	backBtn.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.1,
		WINDOW_HEIGHT * 0.8));
	
	// Set the text "Back" and it's position the instruction screen
	setTextTitles(backBtnTxt, "Back",
		WINDOW_WIDTH * 0.17, WINDOW_HEIGHT * 0.82);

	// Set the text "Game icons:" and it's position the 
	// instruction screen
	setTextTitles(gameIconsTxt, "Game icons:",
		WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.2);
	
	// Set the text  "How to play" and it's position the 
	// instruction screen
	setTextTitles(gameDescTitleTxt, "How to play",
		WINDOW_WIDTH * 0.6, WINDOW_HEIGHT * 0.2);

	gameDescTxt.setCharacterSize(30);
	gameDescTxt.setFont(*r.getArialfont());
	gameDescTxt.setString(GAME_DESC);
	gameDescTxt.setStyle(sf::Text::Bold);
	gameDescTxt.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.6,
		WINDOW_HEIGHT * 0.3));


	setItemDesc(player, PLYAER_STAND, playerTxt, "Player:",
		0, WINDOW_HEIGHT * 0.3);
	setItemDesc(enemy, ENEMY_STAND, enemyTxt, "Enemy:",
		0, WINDOW_HEIGHT * 0.4);
	setItemDesc(coin, COIN, coinTxt, "Coin:",
		0, WINDOW_HEIGHT * 0.5);
	setItemDesc(gift, GIFT, giftTxt, "Gift:",
		0, WINDOW_HEIGHT * 0.6);
}


//------------------------- setItemDesc --------------------------
// Sets the disered distance between the latters and the 
// gameObjectTextures 
//----------------------------------------------------------------
void InstructionScreen::setItemDesc(sf::RectangleShape& gameObject,
	const int textureNum, sf::Text& objectDescText,
	const std::string& objectDescStr,
	const int pos_x, const int pos_y)
{
	gameObject.setTexture(Resources::instance().
		getGameObjectTexture(textureNum));

	// Set the position of the gameObject in the instruction screen
	gameObject.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.3, pos_y));

	// Set the font - gets the font from the resources
	objectDescText.setFont((*Resources::instance().getArialfont()));

	// Set the desired string sended as a parameter
	objectDescText.setString(objectDescStr);

	// Set the position of the objectDescText in the instruction screen
	objectDescText.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.1, pos_y));

	// Set the charcter size
	objectDescText.setCharacterSize(50);
}


//------------------------ setTextTitles --------------------------
// Sets the texts titles.
// Auxillary function to set the desired text title.
// The auxillary function gets a titleTxt and the desired string 
// and it's position and sets the text with those parametrs.
//-----------------------------------------------------------------
void InstructionScreen::setTextTitles(sf::Text &titleTxt,
	std::string str, const int pos_x, const int pos_y) 
{	
	// Set the charcter size
	titleTxt.setCharacterSize(50);

	// Set the font - gets the font from the resources
	titleTxt.setFont((*Resources::instance().getArialfont()));

	// Set the desired string 
	titleTxt.setString(str);

	// set the text style -  Underlined text
	titleTxt.setStyle(sf::Text::Underlined);

	// Set the position of the text
	titleTxt.setPosition(sf::Vector2f(pos_x, pos_y));
}
