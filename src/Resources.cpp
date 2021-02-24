#pragma once 
#include "Resources.h"


// c-tor
Resources::Resources()
{
	// set the static gameObjectTextures
	setStaticTextures();

	// set the player gameObjectTextures
	setPlayerTextures();

	// set the enemy gameObjectTextures
	setEnemyTextures();

	//	set the general window objects
	setWindowObjectTextures();

	// set the sounds buffers
	setSoundBuffer();

	// set the music soundtrack
	setMusicSound();

	dataWindowFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}


//-------------- instance ----------------
// Retrun pointer to the single object 
// of class Resources.
//----------------------------------------
Resources& Resources::instance()
{
	static Resources instance;
	
	return instance;
}

// d-tor
Resources::~Resources()
{}


//------------------- getGameObjectTexture ----------------------
// Return the texture, hold in the vector m_gameObjectTextures,
// in index i.
//-----------------------------------------------------
sf::Texture* Resources::getGameObjectTexture(const int& i) 
{
	return &(m_gameObjectTextures[i]);
}


//------------------- getGameObjectTexture ----------------------
// Return the texture, hold in the vector m_gameObjectTextures,
// in index i.
//-----------------------------------------------------
sf::Texture* Resources::getWindowObjectTexture(const int& i)
{

	return &(m_windowObjectTextures[i]);
}


//------------------- getGameObjectTexture ----------------------
// Return the sound buffer, hold in the vector m_soundsBuffer,
// in index i.
//---------------------------------------------------------------
sf::SoundBuffer* Resources::getSoundBuffer(const int& i)
{
	return &(m_soundsBuffer[i]);
}


//------------------------ setStaticTextures ---------------------------
// Loads all the static gameObjectTextures of the game and inserts
// them in the vector that hold all the gameObjectTextures of the game.
//----------------------------------------------------------------------
void Resources::setStaticTextures()
{
	sf::Texture texture;

	texture.loadFromFile("ladder.png");                 // 0
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("floor.png");					// 1
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("coin.png");					// 2
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("pipe.png");					// 3
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("gift.png");					// 4
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("enemy_gift.png");				// 5
	m_gameObjectTextures.push_back(texture);
}


//---------------------- setPlayerTextures ------------------------
// Loads all the players gameObjectTextures in the game and 
// inserts them in the vector that hold all the gameObjectTextures
// of the game.
//-----------------------------------------------------------------
void Resources::setPlayerTextures()
{
	sf::Texture texture;

	texture.loadFromFile("player_running.png");			// 6
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_stand.png");			// 7
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_stand_anime.png");		// 8
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_climb.png");			// 9
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_climbing.png");	    // 10
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_pipe.png");			// 11
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_falling.png");			// 12
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("player_strike.png");			// 13
	m_gameObjectTextures.push_back(texture);
}


//-------------------------- setEnemyTextures --------------------------
// Loads all the enemy gameObjectTextures in the game and inserts
// them in the vector that hold all the gameObjectTextures of the game.
//----------------------------------------------------------------------
void Resources::setEnemyTextures()
{
	sf::Texture texture;

	texture.loadFromFile("enemy_stand.png");           // 14
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("enemy_running.png");         // 15
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("enemy_pipe.png");            // 16
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("enemy_fall.png");            // 17
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("enemy_climb.png");           // 18
	m_gameObjectTextures.push_back(texture);
	texture.loadFromFile("enemy_climbing.png");        // 19
	m_gameObjectTextures.push_back(texture);
}


//------------------- setWindowObjectTextures ---------------------
// Sets the windows objects textures.
//-----------------------------------------------------------------
void Resources::setWindowObjectTextures()
{
	sf::Texture texture;
	texture.loadFromFile("data_menu.png");				// 0
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("button.png");					// 1
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("button_hover.png");			// 2
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("play_music.png");				// 3
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("mute_music.png");				// 4
	m_windowObjectTextures.push_back(texture);
	texture.loadFromFile("background.png");				// 5
	m_windowObjectTextures.push_back(texture);
}


//----------------------- setSoundBuffer -------------------------
// Sets the sounds that appear in the game when an event happends.
//----------------------------------------------------------------
void Resources::setSoundBuffer()
{
	sf::SoundBuffer soundBuf;
	soundBuf.loadFromFile("coin_collect.wav");		
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("gift_collect.wav");		
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("button_click.wav");		
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("strike_sound.wav");
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("destroyed_sound.wav");
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("lose_sound.wav");
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("win_game_sound.wav");
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("enemy_hit.wav");
	m_soundsBuffer.push_back(soundBuf);

	soundBuf.loadFromFile("enemy_gift_sound.wav");
	m_soundsBuffer.push_back(soundBuf);
}


//----------------------- setMusicSound ------------------------
//              Sets the music sound of the game
//--------------------------------------------------------------
void Resources::setMusicSound()
{
	m_gameSoundTrack.openFromFile("load_runner_sountrack.ogg");
	m_gameSoundTrack.setVolume(8);
}


//------------------- collectCoinSound ---------------------
//           Play the sound of collecting a coin 
//----------------------------------------------------------
void Resources::collectCoinSound()
{
	m_sound.setBuffer(m_soundsBuffer[COLLECT_COIN]);
	m_sound.setVolume(10);
	m_sound.play();
}


//------------------ collectGiftSound ---------------------
//          Play the sound of collecting a gift 
//---------------------------------------------------------
void Resources::collectGiftSound() 
{
	m_sound.setBuffer(m_soundsBuffer[COLLECT_GIFT]);
	m_sound.setVolume(10);
	m_sound.play();
}


//------------------ collectGiftSound ---------------------
//          Play the sound of collecting a enemy gift 
//---------------------------------------------------------
void Resources::collectEnemyGiftSound()
{
	m_sound.setBuffer(m_soundsBuffer[ENEMY_GIFT_COLLECT]);
	m_sound.setVolume(10);
	m_sound.play();
}

//------------------ collectGiftSound ---------------------
//          Plays the sound of pressing a button
//---------------------------------------------------------
void Resources::buttonClickedSound() 
{
	m_sound.setBuffer(m_soundsBuffer[BUTTON_CLICKED]);
	m_sound.setVolume(10);
	m_sound.play();
}


//--------------------- strikeSound -----------------------
//          Plays the sound of x, z buttons
//---------------------------------------------------------
void Resources::strikeSound()
{
	m_sound.setBuffer(m_soundsBuffer[STRIKE]);
	m_sound.setVolume(10);
	m_sound.play();
}


//--------------------- strikeSound -----------------------
//          Plays the sound of x, z buttons
//---------------------------------------------------------
void Resources::playerHitSound()
{
	m_sound.setBuffer(m_soundsBuffer[ENEMY_HIT]);
	m_sound.setVolume(10);
	m_sound.play();
}


//-------------------- blockDestroyedSound ----------------
//          Plays the sound of x, z buttons
//---------------------------------------------------------
void Resources::blockDestroyedSound()
{
	m_sound.setBuffer(m_soundsBuffer[DESTROYED_BLOCK]);
	m_sound.setVolume(10);
	m_sound.play();
}


//--------------------- strikeSound -----------------------
//          Plays the sound of x, z buttons
//---------------------------------------------------------
void Resources::loseSound()
{
	m_sound.setBuffer(m_soundsBuffer[LOSE_GAME]);
	m_sound.setVolume(10);
	m_sound.play();
}


//--------------------- strikeSound -----------------------
//          Plays the sound of x, z buttons
//---------------------------------------------------------
void Resources::winSound()
{
	m_sound.setBuffer(m_soundsBuffer[WIN_GAME]);
	m_sound.setVolume(10);
	m_sound.play();
}


//------------------- isMusicPlayed -----------------------
//          Return the music status (on or off).
//---------------------------------------------------------
bool Resources::isMusicPlayed()
{
	return (m_gameSoundTrack.getStatus() ==
		sf::SoundSource::Status::Playing);
}


//------------------- playSoundTrack ----------------------
//                 Turn on the soundTrack
//---------------------------------------------------------
void Resources::playSoundTrack()
{
	m_gameSoundTrack.setLoop(true);
	m_gameSoundTrack.play();
}


//------------------ turnOffSoundTrack --------------------
//                Turn off the soundTrack
//---------------------------------------------------------
void Resources::turnOffSoundTrack()
{
	m_gameSoundTrack.stop();
}


//------------------- getArialfont ------------------------
//                  Return arial font
//---------------------------------------------------------
const sf::Font* Resources::getArialfont() const 
{
	return &dataWindowFont;
}