#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

//Abstract class
class StaticObject: public GameObject
{
public:

	// c-tor
	StaticObject(const int height, const int width,
		sf::Vector2f position, sf::Texture* texture);

	// d-tor
	virtual ~StaticObject();

	// Draw the static object
	virtual void  draw (sf::RenderWindow& window)  override;

	virtual void handleDig(sf::Vector2f position) = 0;

private:
};