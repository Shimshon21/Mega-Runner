#pragma once

//----------------- include section ------------------
#include "SFML/Graphics.hpp"

//---------------- class section ------------------
class Block;
class Ladder;
class Coin;
class Pipe;
class Player;
class Enemy;
class BonusGift;
class EnemyBonusGift;
class LifeBonusGift;
class ScoreBonusGift;
class TimeBonusGift;


//----------------- GameObject class -------------------
class GameObject {
public:

	// c-tor
	GameObject(sf::Texture* texture,
		const sf::Vector2f position,
		const int height, const int width);

	// c-tor - default
	GameObject();

	// d-tor
	virtual ~GameObject();

	// Set the gameObject texture
	void setTexture(sf::Texture *texture);

	// Set the position of the gameObject
	void setPosition(const sf::Vector2f position);

	// Set the origin of the gameObject - for calculations
	void setOrigin(const sf::Vector2f origin);

	// Return the shape of the game object
	virtual sf::RectangleShape getShape() const;

	// Return the gameObject texture
	sf::Texture* getGameObjectTexture();

	// Return the size of the gameObject
	const sf::Vector2f getSize() const;

	// Return the position of the gameObject
	const sf::Vector2f getPostition() const;

	virtual void draw(sf::RenderWindow& window) = 0;

    virtual void handleCollision(GameObject& gameObject) = 0;

	virtual void handleCollision(Player& gameObject) = 0;

	virtual void handleCollision(Enemy& gameObject) = 0;

	virtual void handleCollision(EnemyBonusGift& gameObject) = 0;

	virtual void handleCollision(LifeBonusGift& gameObject) = 0;

	virtual void handleCollision(ScoreBonusGift& gameObject) = 0;

	virtual void handleCollision(TimeBonusGift& gameObject) = 0;

	virtual void handleCollision(Ladder& gameObject) = 0;

	virtual void handleCollision(Block& gameObject) = 0;

	virtual void handleCollision(Coin& gameObject) = 0;

	virtual void handleCollision(Pipe& gameObject) = 0;

	// check if the player collides with another object in the world
	bool checkCollision(const sf::FloatRect& floatRect1,
		const sf::FloatRect& floatRect2) const;

	// check if the object should be dissposed
	bool isDisposed() const;

	// Set the color of the gameObject
	void setFillColor(sf::Color color);

protected:

	// To have knowlege about things that happen
	bool m_isDisposed = false;

	bool m_addTime = false;

private:
	// to hold the texture
	sf::Texture* m_texture;

	sf::Sprite m_sprite;

	// To hold the shape of an object.00
	sf::RectangleShape m_shape;

	int m_height = 0, m_width = 0;


	// To hold the position of an object.
	sf::Vector2f m_position;
};