#include "Bullet.h"

Bullet::Bullet(sf::Sprite sprite)
{
	

	float TargetRotation = sprite.getRotation();
	m_sprite.setRotation(static_cast<float>(fmod(TargetRotation, 360)));
	float bulletRotation = m_sprite.getRotation();
	if (bulletRotation < 0)
	{
		m_sprite.setRotation(bulletRotation + 360.f);
	}

	m_shape.setPosition(sprite.getPosition());
	m_shape.setRadius(5);
	m_shape.setFillColor(sf::Color::Red);

	m_isAlive = true;

	if (!m_texture.loadFromFile("Assets\\Images\\laserBolt.png"))
	{
		std::cout << "Error: Could not load bullet texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	m_sprite.setScale(0.2, 0.2);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
	//m_shape.setPosition(m_shape.getPosition().x * m_velocity.x, m_shape.getPosition().y * m_velocity.y);

	timer = lifeClock.getElapsedTime();

	float BulletX = m_sprite.getPosition().x + cos(m_sprite.getRotation()*(acos(-1) / 180)) * 20;
	float BulletY = m_sprite.getPosition().y + sin(m_sprite.getRotation()*(acos(-1) / 180)) * 20;



	m_sprite.setPosition(BulletX, BulletY);


	if (timer.asSeconds() > 2)
	{
		m_isAlive = false;
	}
	
}

void Bullet::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

bool Bullet::isAlive()
{
	return m_isAlive;
}
