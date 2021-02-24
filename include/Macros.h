#pragma once 
#include <SFML/Graphics.hpp>

//------------------ window consts----------------------------
const int WINDOW_HEIGHT = 1080, WINDOW_WIDTH = 1920;



//------------------ board consts----------------------------
const int BOARD_WINDOW_HEIGHT = WINDOW_HEIGHT * 0.85,
BOARD_WINDOW_POS_Y = WINDOW_HEIGHT * 0.15;



//------------------ icons consts----------------------------
const char
PLAYER_ICON = '@',
BLOCK_ICON = '#',
COIN_ICON = '*',
LADDER_ICON = 'H',
ENEMY_ICON = '%',
PIPE_ICON = '-',
EMPTY_ICON = ' ',
SAVE_ICON = 's',
CLEAR_ICON = 'c',
NOTHING_ICON = 'n',
GIFT_ICON = '+';


//---------------- player consts -------------------
const float PLAYER_SPEED = 400.f;
const float PLAYER_FALL_SPEED = 700.f;
const int PLAYER_LIVES = 3;


//---------------- coin consts -------------------
const int 
COIN_WIDTH = 20,
COIN_REC_SIZE = 56,
COIN_RECT_WIDTH = 12,
COIN_RECT_HEIGHT = 18;


//---------------- bonousGift consts -------------------
const int 
GIFT_REC_SIZE = 52,
GIFT_WIDTH = 14,
GIFT_HEIGHT = 18,
BONUS_GIFT_WIDTH = 26;


//---------------- font consts -------------------
const int DATA_WINDOW_SIZE_FONT=40;

//---------------- colors consts -------------------
const sf::Color BLUE_CYAN = sf::Color(128, 192, 248);


//------------------- Player consts ------------------------
const int
PLAYER_RUNNING_WIDTH = 38,
PLAYER_RUNNING_HEIGHT = 48,
PLAYER_RUNNING_REC_SIZE = 380,

PLAYER_FALLING_WIDTH = 44,
PLAYER_FALLING_HEIGHT = 61,
PLAYER_FALLINING_REC_SIZE = 150,

PLAYER_CLIMBING_WIDTH = 33,
PLAYER_CLIMBING_HEIGHT = 57,
PLAYER_CLIMBING_REC_SIZE = 165,

PLAYER_STANDING_WIDTH = 44,
PLAYER_STANDING_HEIGHT = 46,
PLAYER_STANDING_REC_SIZE = 210,


NEW_ENEMY_WIDTH = 57,
NEW_ENEMY_HEIGHT = 99,

ENEMY_CLIMB_WIDTH = 45,
ENEMY_CLIMB_HEIGHT = 74,


PLAYER_STRIKE_WIDTH = 130,
PLAYER_STRIKE_HEIGHT = 42,
PLAYER_STRIKE_REC_SIZE = 650;

//------------------- Enemy consts --------------------------
const int
CONSTANT_ENEMY = 1,
NORMAL_ENEMY = 2,
TRACKING_ENEMY = 3,

CONSTANT_ENEMY_SPEED = 300.f,
TRACKING_ENEMY_SPEED = 200.f,
ENEMY_SCALE = 1,

CONSTANT_ENEMY_MOVE_LEFT = 2,
CONSTANT_ENEMY_MOVE_RIGHT = 4,
PUSH_BACK_BLOCK = 5,


ENEMY_RUNNING_WIDTH = 48,
ENEMY_RUNNING_HEIGHT = 58,
ENEMY_RUNNING_REC_SIZE = 720,

ENEMY_CLIMBING_WIDTH = 38,
ENEMY_CLIMBING_HEIGHT = 73,
ENEMY_CLIMBING_REC_SIZE = 228,

ENEMY_PIPE_WIDTH = 36,
ENEMY_PIPE_HEIGHT = 76,

// player and enemy movements - for switch()
UP = 1,
DOWN = 2,
LEFT = 3,
RIGHT = 4,

// player and enemy pipe fall size
PIPE_FALL = 9;


//------------------- Bonus gifts consts -----------------------
const int
LIFE_BONUS = 1,
SCORE_BONUS = 2,
TIME_BONUS = 3,
ENEMY_BONUS = 4;


//------------------- InstructionScreen const ------------------
const std::string GAME_DESC = 
"Player can move by keyboard arrows.\n\
The allowd movment are:\n\
On Floor Right and Left,\n\
On Ladder to all diractions \n\
On pipe Left, Right and Bottom \n\n\
The Player can destroy the Floor\n\
to prevent from Enemy from moving:\n\
Press Z to destroy left Floor\n\
Press X to destroy right Floor\n\n\
Volume Option:\n\
To Mute or Unmute the soundTrack:\n\
press M key or volume logo\n\n\
The Goal:\n\
Collect all coins in all stages without\n\
losing all lifes.\n\n";
