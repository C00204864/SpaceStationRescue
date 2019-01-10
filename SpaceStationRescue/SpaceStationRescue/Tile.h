#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
public:
	// Public Methods
	Tile(float xPos, float yPos);
	~Tile();
	void render(sf::RenderWindow & window);
	void setAsWall(sf::Texture & texture, float sideLength);
	bool isWall();
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

private:
	// Private Members
	sf::Sprite m_sprite;
	bool m_isWall;
};

#endif // !TILE_H
