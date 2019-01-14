#ifndef WORLD_H
#define WORLD_H

// STD Includes
#include <queue>
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
	// Public Functions
	World(std::string loadFilePath, int width, int height, Player & playerIn);
	~World();
	void update(float dt);
	void render(sf::RenderWindow & window);
	Tile & getTileReference(int xIndex, int yIndex);
private:
	// Private Functions
	void setFlowField(int playerIndexX, int playerIndexY, bool processToCompletion);
	void expand(Tile * tile);

	// Private Members
	std::vector<std::vector<Tile>> m_worldGrid;
	std::vector<sf::Texture> m_tileTextures;
	std::queue<Tile *> m_flowFieldQueue;
	sf::Vector2i m_dimensions;
	const int TILE_SIDE_LENGTH = 60;
	const int TILE_TYPES = 9;
	const int FLOW_FIELD_LOOP_COUNT = 200;
	Player & m_refPlayer;
};

#endif // !WORLD_H
