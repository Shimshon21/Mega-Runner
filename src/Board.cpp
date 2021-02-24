#include "Board.h"
#include <fstream>
#include "Block.h"
#include "Ladder.h"
#include "Pipe.h"
#include "Coin.h"
#include "BonusGift.h"
#include "Macros.h"
#include "Resources.h"
#include "LifeBonusGift.h"
#include "ScoreBonusGift.h"
#include "TimeBonusGift.h"
#include "EnemyBonusGift.h"
#include "Controller.h"

// c-tor
Board::Board(Controller* controller)
{
    m_controller = controller;
    setBackground();
}


// d-tor
Board::~Board()
{}


//-------------------- intializeNewBoard ------------------------
// Set the board. Set all the needed data of the world to begin
// playing the game. We enter this function in the begining of
// the game and every time we lose or passed to the next stage
// of the game.
//---------------------------------------------------------------
void Board::intializeNewBoard(const int& height,
    const int& width, std::ifstream& boardFile)
{

    // Number of coins in the begining is zero
    countCoins = 0;

    // The stage goes up by 1
    m_stage++;

    setBoardSize(height, width);

    setIntialBoard(boardFile);

    setBoardGameObjects();
}


//---------------------- setBoardSize -------------------------
// Set the size of the board that holds the data of the world.
//-------------------------------------------------------------
void Board::setBoardSize(const int& height, const int& width)
{
    m_height = height;
    m_width = width;
}


//------------------ getStaticObject ----------------------
// Return current object in index player_index.
//---------------------------------------------------------
StaticObject& Board::getStaticObject(const int& i) const
{
    // return the object in index player_index
    return *(m_staticObjects[i]);
}


//------------------ getMoveObject ----------------------
// Return current object in index player_index.
//---------------------------------------------------------
MoveObject& Board::getMoveObject(const int& i) const
{
    // return the object in index player_index
    return  m_controller->getMoveObject(i);
}


//------------------ getMoveObjectSize --------------------
//            Return size of moveObject vector.
//---------------------------------------------------------
int Board::getMoveObjectSize() 
{
    return m_controller->getMoveObjectsSize();
}



//---------------- getCountCoins ------------------
// Return the  number of coins that exist in world.
//-------------------------------------------------
const unsigned int Board::getCountCoins() const
{
    return countCoins;
}


//------------- reloadBoard ------------------
//        Reload the the board data.
//--------------------------------------------
void Board::reloadBoard()
{
    setBoardGameObjects();
}


//------------------- setBoardGameObjects -----------------------
//         Set map all objects recived from board.txt.
//---------------------------------------------------------------
void Board::setBoardGameObjects()
{
    char gameObjectType;

    sf::Vector2f position;

    // clear the vector that hold the static objects 
    m_staticObjects.clear();

    // clear the vector that hold the moveable objects 
    m_controller->clearVectorMoveObject();

    // new map --> zero coins
    countCoins = 0;


    // run over the objects and set them in the m_staticObjects vector
    for (int i = 0; i < m_height; i++) 
    {
        for (int j = 0; j < m_width; j++) 
        {
            position.x = ((j) * (WINDOW_WIDTH / m_width));
            position.y = ((i) * (BOARD_WINDOW_HEIGHT / m_height))
                + BOARD_WINDOW_POS_Y;

            setGameObjectsVector(i, j, position);
        }
    }
}


//-------------------- setGameObjectsVector ----------------------
//               Set the statics objects vector.
//              ---------------------------------
// The funcion gets a row and col, checks what charcter the 
// m_intlizeMap vector hold in that index and accordingly inserts 
// the object into the vector that hold the gameObjects
//----------------------------------------------------------------
void Board::setGameObjectsVector
(const int& row, const int& col, const sf::Vector2f& position)
{
    int gameObjectType = m_intlizeMap[row][col];      
    Resources &m_resources = Resources::instance();

    switch (gameObjectType)
    {
        // Insert player into the vector of moveObjects
    case PLAYER_ICON:
        m_playerIndex = getMoveObjectSize();
        m_controller->setPlayerObject
        (Player(position, this, BOARD_WINDOW_HEIGHT * 0.9 / m_height,
            WINDOW_WIDTH * 0.7 / m_width));
        break;

    case ENEMY_ICON:
        // Insert a random type of enemt into the vector of moveObjects
        setEnemiesIntoVector((rand() % 3) + 1, position);
        break;

    case LADDER_ICON:
        // Insert ladder into the vector of static objects
        m_staticObjects.push_back(std::make_unique<Ladder>
            (BOARD_WINDOW_HEIGHT / m_height, WINDOW_WIDTH / m_width,
                position, m_resources.getGameObjectTexture(LADDER)));
        break;

    case BLOCK_ICON:
        // Insert block into the vector of static objects
        m_staticObjects.push_back(std::make_unique<Block>
            (BOARD_WINDOW_HEIGHT * 0.8 / m_height, WINDOW_WIDTH / m_width,
                position, m_resources.getGameObjectTexture(BLOCK)));
        break;

    case COIN_ICON:
        // Insert coin into the vector of static objects
        m_staticObjects.push_back(std::make_unique<Coin>
            (WINDOW_HEIGHT * 0.5 / m_height, WINDOW_WIDTH * 0.5 / m_width,
                position, m_resources.getGameObjectTexture(COIN)));
        countCoins++;
        break;

    case PIPE_ICON:
        // Insert pipe into the vector of static objects
        m_staticObjects.push_back(std::make_unique<Pipe>
            (BOARD_WINDOW_HEIGHT*0.2 / m_height, WINDOW_WIDTH / m_width,
                position, m_resources.getGameObjectTexture(PIPE)));
        break;

    case GIFT_ICON:
        // Insert gift into the vector of static objects
        setGiftIntoVector(row, col, position,
            m_resources.getGameObjectTexture(GIFT));
        break;
    default:
        break;
    }
}


//------------------------ setGiftIntoVector ----------------------------
// Set the gift objects in the game.
// The type of gifts are set buy random.
//-------------------------------------------------------------------
void Board::setGiftIntoVector(const int& row, const int& col,
    const sf::Vector2f& position, sf::Texture* texture)
{
    switch (auto gift_type = (rand() % 4) + 1)
    {
    case LIFE_BONUS:
        // Insert a LifeBonusGift into the game.
        m_staticObjects.push_back(std::make_unique<LifeBonusGift>
            (BOARD_WINDOW_HEIGHT / m_height, WINDOW_WIDTH * 0.5 / m_width,
                position, texture));
        break;
    case SCORE_BONUS:
        // Insert a ScoreBonusGift into the game.
        m_staticObjects.push_back(std::make_unique<ScoreBonusGift>
            (BOARD_WINDOW_HEIGHT / m_height, WINDOW_WIDTH * 0.5 / m_width,
                position, texture));
        break;
    case TIME_BONUS:
        // Insert a TimeBonusGift into the game.
        m_staticObjects.push_back(std::make_unique<TimeBonusGift>
            (BOARD_WINDOW_HEIGHT / m_height, WINDOW_WIDTH * 0.5 / m_width,
                position, texture));
        break;
    case ENEMY_BONUS:
        // Insert a EnemyBonusGift into the game
        m_staticObjects.push_back(std::make_unique<EnemyBonusGift>
            (BOARD_WINDOW_HEIGHT / m_height, WINDOW_WIDTH * 0.5 / m_width,
                position, texture));
        break;
    default:
        break;
    }
}


//------------------------- setBackground --------------------------
// Set the board background data and texture.
//------------------------------------------------------------------
void Board::setBackground()
{
    // Set the backGround texture
    m_backGroundTexure.loadFromFile("background.png");

    m_backGroundTexure.setSmooth(true);
    
    // Set the position of the background
    m_backgound.setPosition(sf::Vector2f(0, (BOARD_WINDOW_POS_Y)));

    // Set the texture of the background
    m_backgound.setTexture(&m_backGroundTexure);

    // Set the size of the background
    m_backgound.setSize({ WINDOW_WIDTH,BOARD_WINDOW_HEIGHT });

    // Set the fill color of the background
    m_backgound.setFillColor(sf::Color::White);
}


//-------------------- setIntialBoard -------------------------
// Save the data of current board given in vector of chars.
// The vector that will hold all the chars of the objects 
// is m_intlizeMap.
//-------------------------------------------------------------
void Board::setIntialBoard(std::ifstream& boardFile)
{
    m_intlizeMap = std::vector< std::vector<char>>(m_height);

    for (int i = 0; i < m_height; i++) {

        m_intlizeMap[i] = std::vector<char>(m_width);

        for (int j = 0; j < m_width; j++) {

            m_intlizeMap[i][j] = boardFile.get();

        }
        // Skip \n
        boardFile.get();
    }

    // Skip 'line'
    boardFile.get();
}


//------------ getPlayerIndex --------------
// Return the players index in the vector
// that hold the moveObjects of the game.
//------------------------------------------
int Board::getPlayerIndex() const
{
    return m_playerIndex;
}


//------------------- getStaticObjectsSize --------------------
// Get the size of the vecor which hold the staticObject.
//---------------------------------------------------------
int Board::getStaticObjectsSize() const
{
    return m_staticObjects.size();
}


//-------------------- removeStaticObject ----------------------
// Get the size of the vecor which hold the staticObject.
//--------------------------------------------------------
void Board::removeStaticObject(const int& i)
{
    m_staticObjects.erase(m_staticObjects.begin() + i);
}


//-------------- getStageNum -----------------
// Return the stage number.
//--------------------------------------------
int Board::getStageNum() const
{
    return m_stage;
}


//-------------- resetStageNum ---------------
// Set stage number to 0
//--------------------------------------------
void Board::resetStageNum()
{
    m_stage = 0;
}


//--------------------- setEnemiesIntoVector ----------------------
// Inser the enemy into the the vector that holds all the moveable
// objects in the world.
// The function Inserts a random enemy.
//-----------------------------------------------------------------
void Board::setEnemiesIntoVector(const int& type,
    const sf::Vector2f& position)
{
    switch (type)
    {
    case CONSTANT_ENEMY:
        // Insert ConstantEnemy into the vector of moveObjects
        m_controller->setConstantEnemyObject(ConstantEnemy(position, this,
            BOARD_WINDOW_HEIGHT * 0.9 / m_height,
            WINDOW_WIDTH * 0.7 / m_width));
        break;

    case NORMAL_ENEMY:
        // Insert NormalEnemy into the vector of moveObjects
        m_controller->setNormalEnemyObject(NormalEnemy(position, this,
                BOARD_WINDOW_HEIGHT * 0.9 / m_height,
                WINDOW_WIDTH * 0.7 / m_width));
        break;

    case TRACKING_ENEMY:
        // Insert TrackingEnemy into the vector of moveObjects
        m_controller->setTrackingEnemyObject(TrackingEnemy(position, this,
                BOARD_WINDOW_HEIGHT * 0.9 / m_height,
                WINDOW_WIDTH * 0.7 / m_width));
        break;
    }
}


//-------------------- insertNewEnemy ---------------------
// Got bad gift --> insert a new randrom type of enemy
// Calls a function that inserts a new moveObject
// into the game. The new moveObject will be a new enemy.
// The type of enemy that will be added into the game will
// be random.
//---------------------------------------------------------
void Board::insertNewEnemy(const sf::Vector2f& position)
{
    setEnemiesIntoVector((rand() % 3) + 1, position);
}


//------------------- draw -----------------------
// Draws the board to the window.
// The function works in the following order:
// 1) Draws the the background.
// 2) Runs over the objects and draw them 
//    on top of the background.
//------------------------------------------------
void Board::draw(sf::RenderWindow& window)
{
    // call a function to draw the background
    window.draw(m_backgound);

    // run over the obejct in the game and draw them
    // on top of the background
    for (int i = 0; i < getStaticObjectsSize(); i++)
    {
        m_staticObjects[i]->draw(window);
    }
}


