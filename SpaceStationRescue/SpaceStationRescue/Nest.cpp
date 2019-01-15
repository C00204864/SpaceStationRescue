#include "Nest.h"

Nest::Nest(sf::Vector2f pos, Player & player, World * world):
	m_refPlayer{player}
{
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

	m_missile = new Missile(m_refPlayer);
}

Nest::~Nest() 
{
	delete m_missile;
}

void Nest::update()
{
	if (m_missile->isAlive())
	{
		m_missile->update();
	}
	else if (getDistance(m_refPlayer.getPosition(), m_sprite.getPosition()) < m_circle.getRadius())
	{
		m_missile->reset(m_sprite.getPosition(), m_sprite.getRotation());
	}
}

void Nest::render(sf::RenderWindow & m_window)
{
	m_window.draw(m_circle);
	m_window.draw(m_sprite);
	if (m_missile->isAlive())
	{
		m_missile->render(m_window);
	}
}

void Nest::spawnNewPredator()
{
}

void Nest::spawnNewMissile()
{
	//m_missiles.push_back(new Missile(m_sprite));
}

sf::Sprite Nest::getSprite()
{
	return m_sprite;
}
