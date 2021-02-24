#include "StaticObject.h"
#include "SFML/Graphics.hpp"


// c-tor
StaticObject::StaticObject(const int height, const int width,
	sf::Vector2f position, sf::Texture* texture) 
	:GameObject(texture,position,height,width)
{}


// d-tor
StaticObject::~StaticObject() {}


//------------------ draw -----------------------
//    Draw the static object on the window 
//-----------------------------------------------
void StaticObject::draw(sf::RenderWindow& window) 
{
	window.draw(getShape());
}