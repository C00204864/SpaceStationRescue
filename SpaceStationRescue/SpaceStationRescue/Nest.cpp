#include "Nest.h"

Nest::Nest(sf::Vector2f pos, Player & player, World * world):
	m_refPlayer{player}
{
	// Setup Nest
	if (!m_texture.loadFromFile("Assets\\Images\\Nest.png"))
	{
		std::cout << "Error: Could not load nest textrue" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(pos);
	m_sprite.setScale(0.1f, 0.1f);
	
	m_circle.setFillColor(sf::Color(255, 0, 0, 45));
	m_circle.setRadius(400);
	
	m_circle.setOrigin(m_circle.getGlobalBounds().width / 2.f, m_circle.getGlobalBounds().height / 2.f);
	m_circle.setPosition(m_sprite.getPosition());

	// Setup Missiles and Predators
	m_missile = new Missile(m_refPlayer);
	for (int i = 0; i < PREADTOR_COUNT; ++i)
	{
		m_predators.push_back(new Predator(world, player));
	}
}

Nest::~Nest() 
{
	delete m_missile;
}

void Nest::update(float dt)
{
	m_missile->update();
	if (!m_missile->isAlive() && getDistance(m_refPlayer.getPosition(), m_sprite.getPosition()) < m_circle.getRadius())
	{
		m_missile->reset(m_sprite.getPosition(), m_sprite.getRotation());
	}
	for (auto & predator : m_predators)
	{
		if (!predator->isAlive())
		{
			predatorSpawnSeconds += dt;
			if(PREDATOR_SPAWN_TIME < predatorSpawnSeconds)
			{
				predatorSpawnSeconds = 0.f;
				predator->reset(m_sprite.getPosition());
			}
		}
		else
		{
			predator->update(dt);
		}
	}
}

void Nest::render(sf::RenderWindow & window)
{
	window.draw(m_circle);
	window.draw(m_sprite);
	m_missile->render(window);
	for (auto & predator : m_predators)
	{
		predator->render(window);
	}
}

void Nest::spawnNewPredator()
{

}


sf::Sprite Nest::getSprite()
{
	return m_sprite;
}

std::vector<Predator *> & Nest::getPredatorVector()
{
	return m_predators;
}
