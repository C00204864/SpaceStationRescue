#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
public:
	// Public Methods
	Tile();
	~Tile();
	void setParameters(float xPos, float yPos, float sideLength, sf::Texture & texture);
	void render(sf::RenderWindow & window);
	bool checkCollision();
	sf::Vector2f getPosition();

private:
	// Private Members
	sf::Sprite m_sprite;
};

#endif // !TILE_H
