#include "Missile.h"

Missile::Missile(Player & player) : m_refPlayer(player), m_isAlive(false)
{
	float bulletRotation = m_sprite.getRotation();
	if (bulletRotation < 0)
	{
		m_sprite.setRotation(bulletRotation + 360.f);
	}

	m_shape.setRadius(5);
	m_shape.setFillColor(sf::Color::Red);

	if (!m_texture.loadFromFile("Assets\\Images\\Missile.png"))
	{
		std::cout << "Error: Could not load bullet texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(0.1, 0.1);
}

Missile::~Missile() {}

void Missile::reset(sf::Vector2f positionIn, float rotationIn)
{
	m_shape.setPosition(positionIn);
	m_sprite.setPosition(positionIn);
	m_sprite.setRotation(static_cast<float>(fmod(rotationIn, 360)));
	float bulletRotation = m_sprite.getRotation();
	if (bulletRotation < 0)
	{
		m_sprite.setRotation(bulletRotation + 360.f);
	}
	m_isAlive = true;
	lifeClock.restart();
}

void Missile::explode()
{
	m_isAlive = false;
}

void Missile::update()
{
	if (lifeClock.getElapsedTime().asSeconds() > 5.f)
	{
		explode();
	}
	else
	{
		seek(m_refPlayer.getPosition());
	}
}

void Missile::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

bool Missile::isAlive()
{
	return m_isAlive;
}

void Missile::seek(sf::Vector2f pos)
{
	float dx = pos.x - m_sprite.getPosition().x;
	float dy = pos.y - m_sprite.getPosition().y;

	rotation = atan2(dy, dx)*(180 / acos(-1));

	if (rotation < 0)
	{
		rotation = 360 - (-rotation);
	}

	m_sprite.setPosition((m_sprite.getPosition().x + cos(rotation*(acos(-1) / 180))* 3.5f), (m_sprite.getPosition().y + sin(rotation*(acos(-1) / 180)) * 3.5f));
	m_sprite.setRotation(std::round(rotation));
}
