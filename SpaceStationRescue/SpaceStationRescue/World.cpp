#include "World.h"

World::World(std::string loadFilePath, int width, int height, Player & playerIn) : m_dimensions(sf::Vector2i(width, height)), m_refPlayer(playerIn)
{
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
			m_worldGrid[i].push_back(Tile(i, j, TILE_SIDE_LENGTH));
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
	sf::Vector2f playerPos = m_refPlayer.getPosition();
	setFlowField(playerPos.x / TILE_SIDE_LENGTH, playerPos.y / TILE_SIDE_LENGTH, true);
}

World::~World() {}

void World::update(float dt)
{
	sf::Vector2f playerPos = m_refPlayer.getPosition();
	int indexX = playerPos.x / TILE_SIDE_LENGTH;
	int indexY = playerPos.y / TILE_SIDE_LENGTH;
	for (int i = indexX - 1; i <= indexX + 1; ++i)
	{
		if (i >= 0 && i < m_dimensions.x)
		{
			for (int j = indexY - 1; j <= indexY + 1; ++j)
			{
				if (j >= 0 && j < m_dimensions.y)
				{
					Tile & tile = m_worldGrid[i][j];
					if (tile.isWall())
					{
						m_refPlayer.checkCollision(tile.getGlobalBounds());
					}
				}
			}
		}
	}
	setFlowField(indexX, indexY, false); // Set flow field for AI
}


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

Tile & World::getTileReference(int xIndex, int yIndex)
{
	return m_worldGrid[xIndex][yIndex]; // This can throw out of bounds exceptions for X and Y
}

void World::setFlowField(int playerIndexX, int playerIndexY, bool processToCompletion)
{
	int count = 0;
	if (m_flowFieldQueue.empty())
	{
		for (auto & vec : m_worldGrid)
		{
			for (auto & tile : vec)
			{
				if (!tile.isWall())
				{
					tile.setVisited(false);
				}
			}
		}
		m_flowFieldQueue.push(&m_worldGrid[playerIndexX][playerIndexY]);
	}
	while (!m_flowFieldQueue.empty() && (processToCompletion || !(count > FLOW_FIELD_LOOP_COUNT)))
	{
		expand(m_flowFieldQueue.front());
		m_flowFieldQueue.pop();
		++count;
	}
}

void World::expand(Tile * tile)
{
	sf::Vector2i indices = tile->getIndices();
	int x = indices.x;
	int y = indices.y;
	if (x > 0 && !m_worldGrid[x - 1][y].isWall() && !m_worldGrid[x - 1][y].isVisited())
	{
		m_worldGrid[x - 1][y].setVisited(true);
		m_worldGrid[x - 1][y].setNext(tile);
		m_flowFieldQueue.push(&m_worldGrid[x - 1][y]);
	}
	if (y > 0 && !m_worldGrid[x][y - 1].isWall() && !m_worldGrid[x][y - 1].isVisited())
	{
		m_worldGrid[x][y - 1].setVisited(true);
		m_worldGrid[x][y - 1].setNext(tile);
		m_flowFieldQueue.push(&m_worldGrid[x][y - 1]);
	}
	if (x < m_dimensions.x - 1 && !m_worldGrid[x + 1][y].isWall() && !m_worldGrid[x + 1][y].isVisited())
	{
		m_worldGrid[x + 1][y].setVisited(true);
		m_worldGrid[x + 1][y].setNext(tile);
		m_flowFieldQueue.push(&m_worldGrid[x + 1][y]);
	}
	if (y < m_dimensions.y - 1 && !m_worldGrid[x][y + 1].isWall() && !m_worldGrid[x][y + 1].isVisited())
	{
		m_worldGrid[x][y + 1].setVisited(true);
		m_worldGrid[x][y + 1].setNext(tile);
		m_flowFieldQueue.push(&m_worldGrid[x][y + 1]);
	}
}