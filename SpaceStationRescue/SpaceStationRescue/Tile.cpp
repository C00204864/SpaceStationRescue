#include "Tile.h"

Tile::Tile() {}

Tile::~Tile() {}

void Tile::setParameters(float xPos, float yPos, float sideLength, sf::Texture & texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(xPos, yPos);
}

void Tile::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

bool Tile::checkCollision()
{
	return true;
}

sf::Vector2f Tile::getPosition()
{
	return m_sprite.getPosition();
}