#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//---------------------- class Resources ----------------------
class Resources
{
public:

	// Return the address of the only object of this class.
	static Resources& instance();

	// d-tor
	~Resources();

	// Return texture in index i.
	sf::Texture* getGameObjectTexture(const int& index) ;

	sf::Texture* getWindowObjectTexture(const int& i);

	// Return soundBuffers in index i
	sf::SoundBuffer* getSoundBuffer(const int& i);
	
	// Return arial font
	const sf::Font* getArialfont() const;

	// Play the sound of collecting a coin 
	void collectCoinSound();

	// Play the sound of collecting a gift 
	void collectGiftSound();

	//Play the sound of collecting a enemy gift 
	void collectEnemyGiftSound();

	// Play the sound of pressing a button 
	void buttonClickedSound();

	//Plays the sound of x, z buttons
	void strikeSound();

	//Plays tge sound of player got hit by enemy.
	void playerHitSound();

	//Plays the sound of destroyed block
	void blockDestroyedSound();

	//Plays the sound when lose game
	void loseSound();

	//Plays the sound when win game
	void winSound();

	// Return the music status (on or off).
	bool isMusicPlayed();
	
	// Turn on the soundTrack
	void playSoundTrack();

	// Turn off the soundTrack
	void turnOffSoundTrack();

private:

	// We don't want more than 1 object of this class.
	// This is a singletone.
	Resources();

	Resources(const Resources&) = default;

	Resources& operator=(const Resources&) = default;

	// Set the static gameObjectTextures of the game.
	void setStaticTextures();

	// Set the players gameObjectTextures of the game.
	void setPlayerTextures();

	// Set the enemies gameObjectTextures of the game.
	void setEnemyTextures();

	// Set general window  gameObjectTextures of the game.
	void setWindowObjectTextures();

	// Set the sounds buffer of the game.
	void setSoundBuffer();

	// set the music soundtrack
	void setMusicSound();

	// vector to hold the gameObjectTextures of the game.
	std::vector<sf::Texture> m_gameObjectTextures;

	// vector to hold the window objects.
	std::vector<sf::Texture> m_windowObjectTextures;

	// Vector to hold all the sounds of the game
	std::vector<sf::SoundBuffer>m_soundsBuffer;
	
	sf::Sound m_sound;

	sf::Music m_gameSoundTrack;

	sf::Font dataWindowFont;
};


// enum to hold the positions in the 
// vector that hold the game sounds 
enum sounds
{
	COLLECT_COIN = 0,
	COLLECT_GIFT = 1,
	BUTTON_CLICKED = 2,
	STRIKE = 3,
	DESTROYED_BLOCK = 4,
	LOSE_GAME = 5,
	WIN_GAME = 6,
	ENEMY_HIT = 7,
	ENEMY_GIFT_COLLECT = 8
};


// enum to hold the positions in the 
// vector that hold the game buttons 
enum windowObjectTextures
{
	DATA_MENU,
	BUTTON,
	BUTTON_HOVER,
	PLAY_MUSIC_BUTTON,
	MUTE_MUSIC_BUTTON,
	BACKGROUND
};


// enum to hold the positions in the
// vector that hold the gameObjectTextures
enum gameObjectTextures
{
	// static objects
	LADDER,
	BLOCK,
	COIN,
	PIPE,
	GIFT,
	ENEMY_GIFT,

	// Player
	PLAYER_RUNNING,
	PLYAER_STAND,
	PLAYER_STAND_ANIME,
	PLAYER_CLIMB,
	PLAYER_CLIMBING,
	PLAYER_PIPE,
	PLYAER_FALLING,
	PLAYER_STRIKE,

	// Enemy
	ENEMY_STAND,
	ENEMY_RUNNING,
	ENEMY_PIPE,
	ENEMY_FALL,
	ENEMY_CLIMB,
	ENEMY_CLIMBING
};