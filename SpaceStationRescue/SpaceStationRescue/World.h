#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class World
{
public:
	World(std::string loadFilePath, int width, int height);
	~World();
	void render(sf::RenderWindow & window);
	void update(float dt);
	Tile & getTileReference(int xIndex, int yIndex);
private:
	std::vector<std::vector<Tile>> m_worldGrid;

	sf::Vector2i m_dimensions;
	const int CELL_SIDE_LENGTH = 40;

	// Textures
	sf::Texture m_tileTexture1;
};

#endif // !WORLD_H
