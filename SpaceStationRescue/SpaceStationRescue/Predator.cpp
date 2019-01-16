#include "Predator.h"

Predator::Predator(World * world, Player & player) : p_world(world), m_isAlive(false), m_refPlayer(player)
{
	if (!m_texture.loadFromFile("Assets\\Images\\PlayerShip.png"))
	{
		std::cout << "Error: Could not load predator texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setRotation(0);
	m_sprite.setScale(0.2, 0.2);
}

Predator::~Predator()
{
}

void Predator::reset(sf::Vector2f positionIn)
{
	m_isAlive = true;
	m_sprite.setPosition(positionIn);
	targetTile = p_world->getTilePointer(positionIn.x / p_world->getTileWidth(), positionIn.y / p_world->getTileWidth());
}

void Predator::explode()
{
	m_isAlive = false;
}

void Predator::update(float dt)
{
	if (m_isAlive)
	{
		sf::Vector2f position = m_sprite.getPosition();
		sf::Vector2f playerPos = m_refPlayer.getPosition();
		if (getDistance(playerPos, m_sprite.getPosition()) < PLAYER_DISTANCE_THRESHOLD)
		{
			seek(playerPos);
			targetTile = p_world->getTilePointer(position.x / p_world->getTileWidth(), position.y / p_world->getTileWidth());
		}
		else
		{
			sf::Vector2f targetPos = targetTile->getCenterPosition();
			seek(targetTile->getCenterPosition());
			if (getDistance(m_sprite.getPosition(), targetPos) < TILE_DISTANCE_THRESHOLD)
			{
				targetTile = targetTile->getNext();
			}
		}
	}
}

void Predator::render(sf::RenderWindow & window)
{
	if (m_isAlive)
	{
		window.draw(m_sprite);
	}
}

bool Predator::isAlive()
{
	return m_isAlive;
}

void Predator::seek(sf::Vector2f targetPosition)
{
	float dx = targetPosition.x - m_sprite.getPosition().x;
	float dy = targetPosition.y - m_sprite.getPosition().y;

	rotation = atan2(dy, dx)*(180 / acos(-1));

	if (rotation < 0)
	{
		rotation = 360 - (-rotation);
	}

	m_sprite.setPosition((m_sprite.getPosition().x + cos(rotation*(acos(-1) / 180))* 3.5f), (m_sprite.getPosition().y + sin(rotation*(acos(-1) / 180)) * 3.5f));
	m_sprite.setRotation(std::round(rotation));
}
