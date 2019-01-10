#ifndef WORLD_H
#define WORLD_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "MathUtil.h"

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
	std::vector<sf::Texture> m_tileTextures;

	sf::Vector2i m_dimensions;
	const int TILE_SIDE_LENGTH = 60;
	const int TILE_TYPES = 9;

	// Textures
	sf::Texture m_tileTexture1;
};

#endif // !WORLD_H
