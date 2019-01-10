#include "World.h"

World::World(std::string loadFilePath, int width, int height) : m_dimensions(sf::Vector2i(width, height))
{
	if (!m_tileTexture1.loadFromFile("Assets\\Images\\test.png"))
	{
		std::cout << "Error: Could not load tile texture" << std::endl;
	}

	for (int i = 0; i < width; ++i)
	{
		m_worldGrid.push_back(std::vector<Tile>());
		for (int j = 0; j < height; ++j)
		{
			m_worldGrid[i].push_back(Tile());
			m_worldGrid[i][j].setParameters(i * CELL_SIDE_LENGTH, j * CELL_SIDE_LENGTH, CELL_SIDE_LENGTH, m_tileTexture1);
		}
	}
}

World::~World() {}

void World::render(sf::RenderWindow & window)
{
	for (auto & vec : m_worldGrid)
	{
		for (auto & tile : vec)
		{
			tile.render(window);
		}
	}
}