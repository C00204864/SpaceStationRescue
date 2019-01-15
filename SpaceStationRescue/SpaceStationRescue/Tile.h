#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
public:
	// Public Methods
	Tile(int xIndexIn, int yIndexIn, int sideLength);
	~Tile();
	void render(sf::RenderWindow & window);
	void setAsWall(sf::Texture & texture, float sideLength);
	bool isWall();
	bool isVisited();
	void setVisited(bool state);
	void setNext(Tile * nextTile);
	Tile * getNext();
	sf::Vector2f getPosition();
	sf::Vector2f getCenterPosition();
	sf::FloatRect getGlobalBounds();
	sf::Vector2i getIndices();

private:
	// Private Members
	Tile * p_nextTile;
	sf::Vector2i m_indices;
	sf::Vector2f m_centerPos;
	sf::Sprite m_sprite;
	bool m_isWall;
	bool m_isVisited;
};

#endif // !TILE_H
