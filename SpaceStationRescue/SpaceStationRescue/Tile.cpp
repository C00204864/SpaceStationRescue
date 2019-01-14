#include "Tile.h"

Tile::Tile(int xIndexIn, int yIndexIn, int sideLength)
	: m_indices(xIndexIn, yIndexIn),
	m_isWall(false) 
{
	m_sprite.setPosition(xIndexIn * sideLength, yIndexIn * sideLength);
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

bool Tile::isVisited()
{
	return m_isVisited;
}

void Tile::setVisited(bool state)
{
	m_isVisited = state;
}

void Tile::setNext(Tile * nextTile)
{
	p_nextTile = nextTile;
}

sf::Vector2f Tile::getPosition()
{
	return m_sprite.getPosition();
}

sf::FloatRect Tile::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2i Tile::getIndices()
{
	return m_indices;
}