#ifndef WORLD_H
#define WORLD_H

// STD Includes
#include <fstream>
#include <string>
#include <vector>
#include <iostream> // FOR DEBUG ONLY

// SFML Includes
#include <SFML/Graphics.hpp>

// Project Includes
#include "Tile.h"
#include "Player.h"

class World
{
public:
	World(std::string loadFilePath, int width, int height, Player & playerIn);
	~World();
	void render(sf::RenderWindow & window);
	bool checkCollision(sf::CircleShape entity);
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
	Player & m_refPlayer;
};

#endif // !WORLD_H
