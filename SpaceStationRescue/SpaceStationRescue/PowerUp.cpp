#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f position)
{
	if (!m_texture.loadFromFile("Assets\\Images\\shield.png"))
	{
		std::cout << "Failed to load shield texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(0.3,0.3);
	m_sprite.setPosition(position);
	m_type = PowerType::SHIELD;
	m_isAlive = true;
}

PowerUp::~PowerUp()
{
}

void PowerUp::update()
{
	m_sprite.setRotation(m_sprite.getRotation() + 1);
}

void PowerUp::draw(sf::RenderWindow & window)
{
	if (m_isAlive)
	{
		window.draw(m_sprite);
	}	
}

bool PowerUp::collisionCheck(sf::Sprite sprite)
{
	if (m_isAlive)
	{
		return m_sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());
	}
	else
	{
		return false;
	}
}

void PowerUp::setAlive(bool b)
{
	m_isAlive = b;
}
