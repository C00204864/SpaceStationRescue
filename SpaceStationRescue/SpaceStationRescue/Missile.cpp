#include "Missile.h"

Missile::Missile(sf::Sprite nestSprite)
{
	float TargetRotation = nestSprite.getRotation();
	m_sprite.setRotation(static_cast<float>(fmod(TargetRotation, 360)));
	float bulletRotation = m_sprite.getRotation();
	if (bulletRotation < 0)
	{
		m_sprite.setRotation(bulletRotation + 360.f);
	}

	m_shape.setPosition(nestSprite.getPosition());
	m_shape.setRadius(5);
	m_shape.setFillColor(sf::Color::Red);

	m_isAlive = true;

	if (!m_texture.loadFromFile("Assets\\Images\\Missile.png"))
	{
		std::cout << "Error: Could not load bullet texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(nestSprite.getPosition().x, nestSprite.getPosition().y);
	m_sprite.setScale(0.1, 0.1);
}

Missile::~Missile()
{
}

void Missile::update(sf::Sprite sprite)
{
	timer = lifeClock.getElapsedTime();


	//float BulletX = m_sprite.getPosition().x + cos(m_sprite.getRotation()*(acos(-1) / 180)) * 20;
	//float BulletY = m_sprite.getPosition().y + sin(m_sprite.getRotation()*(acos(-1) / 180)) * 20;

	seek(sprite.getPosition());

	//m_sprite.setPosition(BulletX, BulletY);
}

void Missile::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

bool Missile::isAlive()
{
	return m_isAlive;
}

void Missile::seek(sf::Vector2f pos)
{
	//currentRotation = sprite.getRotation();


	float dx = pos.x - m_sprite.getPosition().x;
	float dy = pos.y - m_sprite.getPosition().y;


	rotation = atan2(dy, dx)*(180 / acos(-1));

	if (rotation < 0)
	{
		rotation = 360 - (-rotation);
	}

	m_sprite.setPosition((m_sprite.getPosition().x + cos(rotation*(acos(-1) / 180))* 1), (m_sprite.getPosition().y + sin(rotation*(acos(-1) / 180))*1));
	m_sprite.setRotation(std::round(rotation));
}
