#include "World.h"

World::World(std::string loadFilePath, int width, int height) : m_dimensions(sf::Vector2i(width, height))
{
	if (!m_tileTexture1.loadFromFile("Assets\\Images\\test.png"))
	{
		std::cout << "Error: Could not load tile texture" << std::endl;
	}

	for (int i = 1; i <= TILE_TYPES; ++i)
	{
		m_tileTextures.push_back(sf::Texture());
		if (!m_tileTextures[i - 1].loadFromFile("Assets\\Images\\Tiles\\Tile" + std::to_string(i) +  ".png"))
		{
			std::cout << "Error: could not load tile texture #" << i << std::endl;
		}
	}

	for (int i = 0; i < width; ++i)
	{
		m_worldGrid.push_back(std::vector<Tile>());
		for (int j = 0; j < height; ++j)
		{
			m_worldGrid[i].push_back(Tile(i * TILE_SIDE_LENGTH, j * TILE_SIDE_LENGTH));
		}
	}

	std::ifstream loader;
	std::string levelLine;
	int yCounter = 0;
	loader.open(loadFilePath);
	while (!loader.eof() && yCounter < m_dimensions.y)
	{
		std::getline(loader, levelLine);
		for (int i = 0; i < levelLine.length() && i < m_dimensions.x; ++i)
		{
			if ('0' != levelLine[i])
			{
				if (isdigit(levelLine[i]))
				{
					m_worldGrid[i][yCounter].setAsWall(m_tileTextures[(int)levelLine[i] - 49], TILE_SIDE_LENGTH);
				}

			}
		}
		++yCounter;
	}
}

World::~World() {}

void World::render(sf::RenderWindow & window)
{
	sf::View currentView = window.getView();
	sf::Vector2f currentViewPosition = currentView.getCenter();
	sf::Vector2f currentViewBounds = currentView.getSize();
	currentViewPosition.x -= currentViewBounds.x / 2.f;
	currentViewPosition.y -= currentViewBounds.y / 2.f;
	sf::FloatRect viewRect = sf::FloatRect(currentViewPosition.x, currentViewPosition.y, currentViewBounds.x, currentViewBounds.y);

	for (auto & vec : m_worldGrid)
	{
		for (auto & tile : vec)
		{
			if (tile.isWall() && viewRect.intersects(tile.getGlobalBounds()))
			{
				tile.render(window);
			}
		}
	}
}