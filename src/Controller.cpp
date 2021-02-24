//------------------- include section -------------------
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>


// c-tor
Controller::Controller()
    : m_window(sf::VideoMode(WINDOW_WIDTH,
        WINDOW_HEIGHT), "Load Runner"),
    m_worldMap(this), 
    mutePlayBtn({0.05*WINDOW_WIDTH,0.05*WINDOW_HEIGHT})
{
    // open the board file.
    m_boardFile.open("Board.txt");

    // load the next board
    loadNextBoard();

    // turn on the game.
    setGameDataWindow();

    // Set the text fonts
    setTextsFonts();
}
    

// d-tor
Controller::~Controller()
{}


//----------------------------------------------------------------
//                          showScreen
//                       ----------------
// Showing the different screen existed in the game.
//----------------------------------------------------------------
void Controller::showScreen()
{
    sf::Clock stageTimer;
    sf::Event event;
    float deltaTime;


    while (m_window.isOpen())
    {
        sf::Event event;

        // Clear the window
        m_window.clear();

        // Start running the game
        if (startGame) {
            runGame(stageTimer, deltaTime, event);
            draw();
        }

        // Open istruction in game menu
        else if (showInstruction)
            openInstruction(event);
        
        // Display the end game window + end game status
        else if (showEndGameScreen)
            openEndGameScreen(event);

        // Exit the game
        else if (!exitGame)
            openMenu(event);

        else
            break;

        // Display the window
        m_window.display();
    }
       
}


//----------------------------------------------------------------
//                          openMenu
//                       ----------------
// Open the menu screen, the screen showing the following buttons:
// Start - allowing the player start the game.
// Instruction - show how to play the game.
// Exit - exit from the game.
//----------------------------------------------------------------
void Controller::openMenu(sf::Event& event)
{
    while (m_window.pollEvent(event))
    {

        switch (event.type)
        {
            // close the window
        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::MouseButtonReleased:

            // Handle a click on a button when mouse button is released.
            m_menu.handleClickButton
            (m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)),
                m_window, exitGame, startGame, showInstruction);
            break;

        case sf::Event::MouseMoved:

            // Handle a the event of the mouse hovering the 
            // buttons of the menu.
            m_menu.handleHoverButton(m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)), m_window);
            break;

        }

    }

    // Draw the menu on the window
    m_menu.draw(m_window);
}


//----------------------------------------------------------------
//                          openInstruction
//                       -------------------
// Open the Instruction screen, the screen show how  to play the 
// game and what each item in the game role.
//----------------------------------------------------------------
void Controller::openInstruction(sf::Event& event)
{
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:

            // Close the window
            m_window.close();
            break;

        case sf::Event::MouseButtonReleased:

            // Handle a click on a button when mouse button is released.
            m_instructScreen.handleMouseButtonReleased
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)), showInstruction);
            break;

        case sf::Event::MouseMoved:

            // Handle a the event of the mouse hovering the 
            // buttons of the instruction screen.
            m_instructScreen.handleHoverButton
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)));
            break;
        }
    }

    m_instructScreen.draw(m_window);
}


//------------------------ openEndGameScreen --------------------------
// Open the window if the player finished all stages, or lost all his 
// lifes he had.
// If he won the game the end game stats will be shown.
//---------------------------------------------------------------------
void Controller::openEndGameScreen(sf::Event& event)
{

    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::MouseButtonReleased:

            // Handle a click on a button when mouse button is released.
            m_endGameScreen.handleMouseButtonReleased
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)), showEndGameScreen);

            break;

        case sf::Event::MouseMoved:

            // Handle a the event of the mouse hovering the 
            // buttons of the end game screen.
            m_endGameScreen.handleHoverButton
            (m_window.mapPixelToCoords
            (sf::Mouse::getPosition(m_window)));

        }
    }

    // Draw the end game screen
    m_endGameScreen.draw(m_window, wonTheGame);
}



//----------------------------------------------------------------
//                          runGame
//                       ----------------
// The main game loop in the program that runs and reads events from
// the user until the player wins, loses or leaves the game.
//----------------------------------------------------------------
void Controller::runGame(sf::Clock& stageTimer,
    float& deltaTime, sf::Event& event)
{
        deltaTime = gameMovementClock.restart().asSeconds();

        if (m_player->getLifes() > -1) 
        {

            // handle the stageTimer in the game.
            stageTimeHandler(stageTimer);

            // handle according to player coins and hit.
            handlePlayerStatus();


            // move the player:
            // Note: we want to move the player first to have 
            // the player position always up-to-date
            m_player->move(deltaTime);


            // move the move objects:
            // run over the moveObjects vector and move all
            // the enemies, skip the hero of the game.
            for (int i = 0; i < m_moveObjects.size(); i++)
            {
                if (i != m_worldMap.getPlayerIndex())
                {
                    // every enemy gets the player 
                    // position in-order to move accordingly
                    m_moveObjects[i].get()->
                        setPlayerPos(m_player->getPosition());

                    // move the current enmey
                    m_moveObjects[i].get()->move(deltaTime);
                }
            }


            while (m_window.pollEvent(event))
            {
                switch (event.type)
                {
                    // close the window
                case sf::Event::Closed:
                    m_window.close();
                    break;

                    // press on volume logo with the mouse to 
                    // mute or unmute the soundtrack 
                case sf::Event::MouseButtonReleased:
                    handleMouseButtonReleased
                    (m_window.mapPixelToCoords
                    (sf::Mouse::getPosition(m_window)));
                    break;

                    // press M on keyboard to 
                    // mute or unmute the soundtrack 
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::M)
                        muteOrPlaySoundTrack();
                    break;
                }
            }
           
            draw();

        }
        // Exit the game
        else {
            startGame = false;
            wonTheGame = false;
            showEndGameScreen = true;
            resetGameData();
            Resources::instance().loseSound();
        }
}



//------------------------ handlePlayerStatus --------------------------
// Get information about the player status in the current stage.
// i.e. if the player got hit, the amount of coins, bonus...
//---------------------------------------------------------------------
void Controller::handlePlayerStatus()
{
    // If the player got hit --> relaod the current stage
    if (m_player->isPlayerGotHit()) 
    {
        reloadMap();
    }


    // If the amount of coins last in the world is zero
    // then add to the player the stage bonus points and 
    // afterwards reload the next stage 
    if (m_worldMap.getCountCoins() == m_player->getCoins())
    {
        m_player->stageBonusAddScore();

        // load the next stage of the game
        loadNextBoard();
    }
}



//---------------------- handleMouseButtonReleased -----------------------
// Hande the event the mouse button is released.
// Check if the the mouse button got released upon the location of the 
// vloume logo.
// If the mouse button has released in that location, then the soundtrack
// of the game is turning on or turning off.
//------------------------------------------------------------------------
void Controller::handleMouseButtonReleased(const sf::Vector2f& location)
{
    //Mute or Play the game soundtrack.
    if (mutePlayBtn.getGlobalBounds().contains(location))
    {
        muteOrPlaySoundTrack();
    }
}



//------------------------ setGameDataWindow --------------------------
// Sets the data of the game. 
// Here we set the data of the game. i.e. the score, health, stage and 
// the time left.
//---------------------------------------------------------------------
void Controller::setGameDataWindow() {

    Resources& resource = Resources::instance();

    // Set the Characteristics of the gameDataWindow.
    //Set the position, size, color and texture.
    m_gameDataWindow.setPosition(0, 0);
    m_gameDataWindow.setSize(sf::Vector2f(WINDOW_WIDTH, 0.15 * WINDOW_HEIGHT));
    m_gameDataWindow.setFillColor(sf::Color::White);
    m_gameDataWindow.setTexture(resource.getWindowObjectTexture(DATA_MENU));


    // Set the score text position on the data window and then set the
    // text characteristics with the function setTextData().  
    m_scoreTxt.setPosition(0.1 * WINDOW_WIDTH, 0.02 * WINDOW_HEIGHT);
    setTextData(m_scoreTxt);

    // Set the health text position on the data window and then set the
    // text characteristics with the function setTextData(). 
    m_healthTxt.setPosition(0.3 * WINDOW_WIDTH, 0.02 * WINDOW_HEIGHT);
    setTextData(m_healthTxt);

    // Set the stage text position on the data window and then set the
    // text characteristics with the function setTextData(). 
    m_stageTxt.setPosition(0.5 * WINDOW_WIDTH, 0.02 * WINDOW_HEIGHT);
    setTextData(m_stageTxt);

    // Set the time text position on the data window and then set the
    // text characteristics with the function setTextData(). 
    m_timeTxt.setPosition(0.7 * WINDOW_WIDTH, 0.02 * WINDOW_HEIGHT);
    setTextData(m_timeTxt);

    mutePlayBtn.setPosition(0.9 * WINDOW_WIDTH, 0.02 * WINDOW_HEIGHT);
    mutePlayBtn.setTexture(resource.getWindowObjectTexture(PLAY_MUSIC_BUTTON));
}


//----------------------- drawGameDataWindow -----------------------
// Draws the game data we setted in the function setGameDataWindow. 
// i.e. draws to the window the score, health, stage and time. 
//------------------------------------------------------------------
void Controller::drawGameDataWindow()
{
        std::string score("Score: "),
            health("Health: "),
            stage("Stage: "),
            time("Time: ");

        // Add to the string "Score: " the score of the player. 
        score += std::to_string(m_player->getScore());
        m_scoreTxt.setString(score);

        // Add to the string "Health: " the amount of
        // lifes the player has. 
        health += std::to_string(m_player->getLifes());
        m_healthTxt.setString(health);

        // Add to the string "Stage: " the current stag number
        stage += std::to_string(m_worldMap.getStageNum());
        m_stageTxt.setString(stage);

        // If the time is not equal to -1, add to the string 
        // time the amount of time last
        if (m_time != -1) 
            time += std::to_string(m_time);
        else 
            time.clear();

        m_timeTxt.setString(time);

        // Draw the players status on the data window above 
        m_window.draw(m_gameDataWindow);
        m_window.draw(m_scoreTxt);
        m_window.draw(m_healthTxt);
        m_window.draw(m_stageTxt);
        m_window.draw(m_timeTxt); 
        m_window.draw(mutePlayBtn);
}


//----------------- setTextData ----------------------
//            Set the texts of the game
//----------------------------------------------------
void Controller::setTextData(sf::Text& m_text)
{
    m_text.setColor(BLUE_CYAN);
    m_text.setCharacterSize(DATA_WINDOW_SIZE_FONT);
    m_text.setStyle(sf::Text::Bold);
}


//---------------------- stageTimeHandler ----------------------
// Handle the time of the game.
// Here we handle the time of the game by counting down
// with the stageTimer(sf::gameMovementClock).
//---------------------------------------------------------
void Controller::stageTimeHandler(sf::Clock& timer)
{

    if (m_time != -1) 
    {
        // Decrease time by 1, every second 
        if (timer.getElapsedTime().asSeconds() >= 1.0f)
        {
            m_time -= 1;
            timer.restart();
        }

        // If the time ends ==> reload the current stage map.
        if (m_time == 0) 
        {
            reloadMap();
        }
    }
}


//-------------------- reloadMap -------------------------
// reloads the map of the game with the needed stats. 
// if you came here , it means you either died or you had
// no time left.
//--------------------------------------------------------
void Controller::reloadMap()
{
    // Decrease the player stage score 
    // --> to the score he beggin the stage 
    m_player->decreaseStageScore();

    // reload the board - set the board to defualt
    m_worldMap.reloadBoard();


    // New player ==> new pointer to the player class.
    // Needed for functions that are not accessible
    // from the base department. 
    // Note: we use static cast because we konw the location 
    // of the player(returned by the function getPlayerIndex()).
    m_player = static_cast<Player*>
        (m_moveObjects[m_worldMap.getPlayerIndex()].get());


    // Hold pointer to m_time, to increase time 
    // from time bonus gift collected.
    m_player->setTime(&m_time);

    // Clear the window
    m_window.clear();

    // decrease players life by 1
    m_player->decLifeByOne();

    // Rest the stage time
    m_time = m_intialStageTime;
}


//----------------------------- draw -------------------------------
// Draws the game.
// Draws all the objects of the game and displays it to the window.
//-------------------------------------------------------------------
void Controller::draw()
{
    float deltaTime = gameMovementClock.getElapsedTime().asSeconds();

    // draw the map first
    m_worldMap.draw(m_window);

    // handle special events
    handlePipeAndFall(deltaTime);

    // run over the move objects and draw them on the window
    for (int i = 0; i < m_moveObjects.size(); i++)
    {
        m_moveObjects[i].get()->draw(m_window);
    }

    // draw the game data up to date
    drawGameDataWindow();

    // display the "new window"
    m_window.display();
}


//---------------------- handlePipeAndFall -------------------------
// Handle pipe - the enemy/player falls and holds the pipe correctly
// handle fall - the enemy/ player fall if they are in air.
//------------------------------------------------------------------
void Controller::handlePipeAndFall(const float& deltaTime)
{
    for (int i = 0; i < m_moveObjects.size(); i++)
    {
        m_moveObjects[i].get()->handlePipe();
        m_moveObjects[i].get()->handleFall(deltaTime);
    }
}


//-------------------- muteOrPlaySoundTrack --------------------
//               Turn on or off the soundTrack.
// r.isMusicPlayed() - Return if the soundtrck of the game
// is playing.
// If the soundtrack of the game is playing - then we turn
// of the soundtrack with the function r.turnOffSoundTrack().
// If the soundtrack of the game is not playing - we turn
// Turn on the soundtrck of the game with the function 
// r.turnOnSoundTrack().
// Also sets the needed sound logo after the volume status
// update.
// Note: shutting off the soundtrack of the game doesn't mean
// that the sound of the game also went off. i.e. sound 
// effects of collecting a gift, coin or getting hit by
// an enemy will remain.
//--------------------------------------------------------------
void Controller::muteOrPlaySoundTrack()
{
    Resources& r = Resources::instance();

    if (r.isMusicPlayed())
    {
        // Turn on the soundtrack
        r.turnOffSoundTrack();

        mutePlayBtn.setSize(sf::Vector2f(0.05 * WINDOW_WIDTH,
            0.05 * WINDOW_HEIGHT));

        mutePlayBtn.setTexture
        (r.getWindowObjectTexture(MUTE_MUSIC_BUTTON));

    }
    else            
    {
        // Turn of the soundtrack
        r.playSoundTrack();

        mutePlayBtn.setTexture
        (r.getWindowObjectTexture(PLAY_MUSIC_BUTTON));
    }
}


//--------------------- setTextsFonts -------------------
// Sets the Texy fronts of the game.
// i.e. sets the texts score, health, stage and time.
//-------------------------------------------------------
void Controller::setTextsFonts()
{
    const Resources& resource = Resources::instance();

    // set score to the window
    m_scoreTxt.setFont(*resource.getArialfont());

    // set health to the window
    m_healthTxt.setFont(*resource.getArialfont());

    // set stage to the window
    m_stageTxt.setFont(*resource.getArialfont());

    // set time to the window
    m_timeTxt.setFont(*resource.getArialfont());
}


//-------------------- loadBoard -----------------------
// Load board data from existed input board.txt file.
//-------------------------------------------------------------
void Controller::loadNextBoard()
{

    if (!m_boardFile.eof()) {
        m_stageNum++;

        // Set the numbers of the height, width and 
        // the amount of time from a file
        setNumFromFile(m_height);
        setNumFromFile(m_width);
        setNumFromFile(m_time);

        m_intialStageTime = m_time;

        // new moveObjects with new locations 
        // ==> clear the vector of moveObjects
        m_moveObjects.clear();

        // Intialize the new board with the new Characteristics
        m_worldMap.intializeNewBoard(m_height, m_width, m_boardFile);
        

        // New player ==> new pointer to the player class.
        // Needed for functions that are not accessible
        // from the base department. 
        // Note: we use static cast because we konw the location 
        // of the player(returned by the function getPlayerIndex()).
        m_player = static_cast<Player*>
            (m_moveObjects[m_worldMap.getPlayerIndex()].get());

        // Set the 
        m_player->setTime(&m_time);
        m_player->resetCoins();
    }   
    else
    {
        startGame = false;
        showEndGameScreen = true;
        wonTheGame = true;
        m_endGameScreen.setWinGameData
        (m_player->getScore(),
            m_worldMap.getStageNum(), m_player->getLifes());
        Resources::instance().winSound();
        resetGameData();
    }
}


//---------------- setNumFromFile ------------------
//            Set the number from a file
//--------------------------------------------------
void Controller::setNumFromFile(int& num) {
    std::string inputNum;
    char numLetter;

    while ((numLetter = m_boardFile.get()) != ' '
        && numLetter != '\n') {
        inputNum.push_back(numLetter);
    }
    num = stoi(inputNum);


    inputNum.clear();
}


//---------------- resetGameData ------------------
// Intilize all game data used to the start game state.
//--------------------------------------------------
void Controller::resetGameData() {

    // Rest stange number
    m_worldMap.resetStageNum();

    // Rest the players stats
    m_player->resetLife();
    m_player->resetCoins();
    m_player->resetScore();

    // dirct the pointer to the begining of the external file.
    m_boardFile.clear();
    m_boardFile.seekg(0, std::ios::beg);
    Resources::instance().turnOffSoundTrack();
    loadNextBoard();
}


//---------------- clearVectorMoveObject ------------------
//        Clear the vector that hold the moveObjects 
//---------------------------------------------------------
void Controller::clearVectorMoveObject()
{
    m_moveObjects.clear();
}


//------------------- clearVectorMoveObject --------------------
// Insert the player into the vector that holds the moveObjects
//--------------------------------------------------------------
void Controller::setPlayerObject(const Player& item)
{
    m_moveObjects.push_back(std::make_unique<Player>(item));
}


//----------------- setConstantEnemyObject --------------------------
// Insert a ConstantEnemy into the vector that holds all the 
// moveObjects of the game. 
//-------------------------------------------------------------------
void Controller::setConstantEnemyObject(const ConstantEnemy& item)
{
    m_moveObjects.push_back(std::make_unique<ConstantEnemy>(item));
}


//-------------------- setNormalEnemyObject -----------------------
// Insert a NormalEnemy into the vector that holds all the 
// moveObjects of the game.  
//-----------------------------------------------------------------
void Controller::setNormalEnemyObject(const NormalEnemy& item)
{
    m_moveObjects.push_back(std::make_unique<NormalEnemy>(item));
}


//--------------------setTrackingEnemyObject ----------------------
// Insert a TrackingEnemy into the vector that holds all the 
// moveObjects of the game.  
//-----------------------------------------------------------------
void Controller::setTrackingEnemyObject(const TrackingEnemy& item)
{
    m_moveObjects.push_back(std::make_unique<TrackingEnemy>(item));
}


//----------------------- getMoveObject ------------------------
// Return moveObject in index i.
//--------------------------------------------------------------
MoveObject& Controller::getMoveObject(const int& i)
{
    // return the object in index player_index
    return *(m_moveObjects)[i];
}


//------------------- getMoveObjectsSize -----------------------
// Return the size of the moveObject vector
//--------------------------------------------------------------
const int Controller::getMoveObjectsSize() const
{
    return m_moveObjects.size();
}