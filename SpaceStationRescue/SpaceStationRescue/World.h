#ifndef WORLD_H
#define WORLD_H

// Predefinitions to deal with circular references
class Nest;
class Predator;

// STD Includes
#include <queue>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// SFML Includes
#include <SFML/Graphics.hpp>

// Project Includes
#include "Tile.h"
#include "Player.h"
#include "Nest.h"
#include "Worker.h"
#include "Sweeper.h"

class Predator;

class World
{
public:
	// Public Functions
	World(std::string loadFilePath, int width, int height, Player & playerIn);
	~World();
	void reset(std::string loadFilePath);
	void load(std::string loadFilePath);
	void update(float dt);
	void render(sf::RenderWindow & window);
	Tile * getTilePointer(int xIndex, int yIndex);
	int getTileWidth();
	int getAliveNests();
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
	const int FLOW_FIELD_LOOP_COUNT = 1000;
	const int NEST_COUNT = 2;
	Player & m_refPlayer;
	std::vector<Nest *> m_nests;
	std::vector<Worker *> m_workers;
	std::vector<Sweeper *> m_sweepers;
};

#endif // !WORLD_H