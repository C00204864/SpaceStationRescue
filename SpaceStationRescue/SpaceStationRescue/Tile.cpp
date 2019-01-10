#include "Tile.h"

Tile::Tile(float xPos, float yPos) : m_isWall(false) 
{
	m_sprite.setPosition(xPos, yPos);
}

Tile::~Tile() {}

void Tile::render(sf::RenderWindow & window)
{
		window.draw(m_sprite);
}

void Tile::setAsWall(sf::Texture & texture, float sideLength)
{
	m_isWall = true;
	m_sprite.setTexture(texture);
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	m_sprite.setScale(sideLength / bounds.width, sideLength / bounds.height);
}
bool Tile::isWall()
{
	return m_isWall;
}

sf::Vector2f Tile::getPosition()
{
	return m_sprite.getPosition();
}

sf::FloatRect Tile::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}