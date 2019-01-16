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
		timer += dt;
		if (timer > 0.25f)
		{
			timer = 0;
			m_sprite.setPosition(targetTile->getCenterPosition());
			targetTile = targetTile->getNext();
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

void Predator::seek(sf::Vector2f pos)
{

}
