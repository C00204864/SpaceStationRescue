#include "Predator.h"

Predator::Predator(World * world, sf::Vector2f positionIn) : p_world(world), m_isAlive(true)
{
	if (!m_texture.loadFromFile("Assets\\Images\\PlayerShip.png"))
	{
		std::cout << "Error: Could not load predator texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(positionIn);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setRotation(0);
	m_sprite.setScale(0.2, 0.2);
	targetTile = p_world->getTilePointer(positionIn.x / p_world->getTileWidth(), positionIn.y / p_world->getTileWidth());
}

Predator::~Predator()
{
}

void Predator::update(float dt)
{
	timer += dt;
	if (timer > 0.25f)
	{
		timer = 0;
		m_sprite.setPosition(targetTile->getCenterPosition());
		targetTile = targetTile->getNext();
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
