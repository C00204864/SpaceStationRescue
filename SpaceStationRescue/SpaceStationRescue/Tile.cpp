#include "Tile.h"

/// <summary>
/// Constructor function for the tile class
/// </summary>
/// <param name="xIndexIn">X Index of the tile in relation to the world grid containing it</param>
/// <param name="yIndexIn">Y Index of the tile in relation to the world grid containing it</param>
/// <param name="sideLength">The desired length for the sides of the tile</param>
Tile::Tile(int xIndexIn, int yIndexIn, int sideLength)
	: m_indices(xIndexIn, yIndexIn),
	m_isWall(false) 
{
	m_sprite.setPosition(xIndexIn * sideLength, yIndexIn * sideLength);
	m_centerPos = sf::Vector2f(xIndexIn * sideLength + sideLength / 2.f, yIndexIn * sideLength + sideLength / 2.f);
}

/// <summary>
/// Destructor function for the tile class
/// </summary>
Tile::~Tile() {}

/// <summary>
/// Render function for the tile class
/// </summary>
/// <param name="window">Reference to the window used for drawing</param>
void Tile::render(sf::RenderWindow & window)
{
		window.draw(m_sprite);
}

/// <summary>
/// Fubction used to set a tile as a wall tile, thus enabling collisions with it
/// </summary>
/// <param name="texture">The texture the tile is to use to represent the wall</param>
/// <param name="sideLength">The length of the sides of a tile</param>
void Tile::setAsWall(sf::Texture & texture, float sideLength)
{
	m_isWall = true;
	m_sprite.setTexture(texture);
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	m_sprite.setScale(sideLength / bounds.width, sideLength / bounds.height);
}

/// <summary>
/// Function returns a boolean representing whether a tile is a wall or not
/// </summary>
/// <returns>Boolean representing whether a tile is a wall or not</returns>
bool Tile::isWall()
{
	return m_isWall;
}

/// <summary>
/// Function used during flow field processing to check whether a cell has been visited oor not
/// </summary>
/// <returns>Boolean representing whether a tile has been visited or not</returns>
bool Tile::isVisited()
{
	return m_isVisited;
}

/// <summary>
/// Function used to set the visited state fo a tile during flow field processing
/// </summary>
/// <param name="state">Desireed visited state</param>
void Tile::setVisited(bool state)
{
	m_isVisited = state;
}

/// <summary>
/// Function used to set the next tile pointed to by *this* in a flow field
/// </summary>
/// <param name="nextTile">The tile this tile is to be pointed to</param>
void Tile::setNext(Tile * nextTile)
{
	p_nextTile = nextTile;
}

/// <summary>
/// Function used to get the next tile pointed to by *this* in a flow field
/// </summary>
/// <returns>The next tile pointed to</returns>
Tile * Tile::getNext()
{
	return p_nextTile;
}

/// <summary>
/// Function gets a vector representing the position of a tile
/// </summary>
/// <returns>sf::Vector2f representing the top left position of a tile</returns>
sf::Vector2f Tile::getPosition()
{
	return m_sprite.getPosition();
}

/// <summary>
/// Function gets a vector representing the center position of a tile
/// </summary>
/// <returns>sf::Vector2f representing the center position of a tile</returns>
sf::Vector2f Tile::getCenterPosition()
{
	return m_centerPos;
}

/// <summary>
/// Functions get the global bounds of the tile's sprite
/// </summary>
/// <returns>sf::FloatRect representing the tile's bounds</returns>
sf::FloatRect Tile::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}

/// <summary>
/// Function gets the X index and Y index of a tile
/// </summary>
/// <returns>sf::Vector2i representing the tile's indices</returns>
sf::Vector2i Tile::getIndices()
{
	return m_indices;
}