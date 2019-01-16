#include "Worker.h"

Worker::Worker(sf::Vector2f pos)
{
	if (!m_texture.loadFromFile("Assets\\Images\\worker.png"))
	{

	}
	m_rotation = 0;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
	m_sprite.setRotation(m_rotation);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(0.15, 0.15);
	m_alive = true;
}

Worker::~Worker()
{
}

void Worker::update()
{

}

void Worker::draw(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_sprite);
	}
}

void Worker::seek(sf::Vector2f pos)
{
	float dx = pos.x - m_sprite.getPosition().x;
	float dy = pos.y - m_sprite.getPosition().y;

	m_rotation = atan2(dy, dx)*(180 / acos(-1));

	if (m_rotation < 0)
	{
		m_rotation = 360 - (-m_rotation);
	}

	m_sprite.setPosition((m_sprite.getPosition().x + cos(m_rotation*(acos(-1) / 180))* 3.5f), (m_sprite.getPosition().y + sin(m_rotation*(acos(-1) / 180)) * 3.5f));
	m_sprite.setRotation(std::round(m_rotation));
}

bool Worker::isAlive()
{
	return m_alive;
}
