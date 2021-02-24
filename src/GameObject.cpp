#pragma once
#include "GameObject.h"


// c-tor
GameObject::GameObject(sf::Texture* texture,
	const sf::Vector2f position, const int height,
	const int width) :
	m_texture(texture),
	m_position(position),
	m_height(height),
	m_width(width)
{
	// Set the size according to the width and height
	m_shape.setSize(sf::Vector2f(m_width, m_height));

	// Set the gameObjects texture
	m_shape.setTexture(texture);

	// Set the gameObjects position in the world
	m_shape.setPosition(position);

	// Set the gameObjects fillcolor 
	m_shape.setFillColor(sf::Color::White);
}


// c-tor - default
GameObject::GameObject() {}


// d-tor
GameObject::~GameObject() {}


//------------------ setTexture --------------------
//            Set the gameObject texture
//--------------------------------------------------
void GameObject::setTexture(sf::Texture* texture)
{
	m_texture = texture;
}


//-------------------- setPosition -----------------------
//             Set the gameObject position
//--------------------------------------------------------
void GameObject::setPosition(const sf::Vector2f position)
{
	m_position = position;
}


//-------------------- setOrigin ------------------------
//			    Set the gameObject origin
//-------------------------------------------------------
void GameObject::setOrigin(const sf::Vector2f origin)
{
	m_shape.setOrigin(origin);
}


//-------------------- getShape ---------------------
//           Return the gameObject shape
//---------------------------------------------------
sf::RectangleShape GameObject::getShape() const
{	
	return m_shape;
}


//------------ getGameObjectTexture ------------
// Return the gameObjects texture - for draw
//----------------------------------------------
sf::Texture* GameObject::getGameObjectTexture()
{
	return m_texture;
}


//----------------- getSize -------------------
//         Return the gameObject size
//---------------------------------------------
const sf::Vector2f GameObject::getSize() const
{
	return sf::Vector2f(m_width, m_height);
}


//----------------- getPostition --------------------
//          Return the gameObject position
//---------------------------------------------------
const sf::Vector2f GameObject::getPostition() const
{
	return m_position;
}


//---------------------- checkCollision ------------------------
//    Return if two gameObjects collide - for double dispach
//--------------------------------------------------------------
bool GameObject::checkCollision(const sf::FloatRect& floatRect1,
	const sf::FloatRect& floatRect2) const
{
	return floatRect1.intersects(floatRect2);
}


//----------------------- isDisposed ------------------------
// Return if the gameObject should be disposed form the game
//-----------------------------------------------------------
bool GameObject::isDisposed() const
{
	return m_isDisposed;
}


//------------------ setFillColor --------------------
//           Set the color of the gameObject
//----------------------------------------------------
void GameObject::setFillColor(sf::Color color)
{
	m_shape.setFillColor(color);
}
