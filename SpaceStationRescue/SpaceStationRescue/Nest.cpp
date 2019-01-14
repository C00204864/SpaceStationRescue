#include "Nest.h"

Nest::Nest(sf::Vector2f pos, Player & player):
	m_player{player}
{
	if (!m_texture.loadFromFile("Assets\\Images\\nest.png"))
	{

	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(pos);
	m_sprite.setScale(0.1f, 0.1f);
	
	m_circle.setFillColor(sf::Color(255, 0, 0, 125));
	m_circle.setRadius(400);
	
	m_circle.setOrigin(m_circle.getGlobalBounds().width / 2.f, m_circle.getGlobalBounds().height / 2.f);
	m_circle.setPosition(m_sprite.getPosition());

}

Nest::~Nest()
{
}

void Nest::update()
{
	for (auto &m : m_missiles)
	{
		m->update(m_player.getSprite());
	}
}

void Nest::draw(sf::RenderWindow & m_window)
{
	m_window.draw(m_circle);
	m_window.draw(m_sprite);
	for (auto &m : m_missiles)
	{
		m->draw(m_window);
	}
}

void Nest::spawnNewPred()
{
}

void Nest::spawnNewMissile()
{
	m_missiles.push_back(new Missile(m_sprite));
}

sf::Sprite Nest::getSprite()
{
	return m_sprite;
}
