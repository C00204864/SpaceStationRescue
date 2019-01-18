#include "Bullet.h"
/// <summary>
/// Constructor for Bullet Object
/// </summary>
/// <param name="position">position to spawn at</param>
/// <param name="rotation">rotation to spawn with</param>
Bullet::Bullet(sf::Vector2f position, float rotation)
{
	m_sprite.setRotation(rotation);

	m_isAlive = true;

	if (!m_texture.loadFromFile("Assets\\Images\\LaserBolt.png"))
	{
		std::cout << "Error: Could not load bullet texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
	m_sprite.setPosition(position);
	m_sprite.setScale(0.2, 0.2);

	m_collisionCircle.setRadius(RADIUS);
	m_collisionCircle.setOrigin(RADIUS, RADIUS);
	m_collisionCircle.setPosition(position);
	m_collisionCircle.setFillColor(sf::Color::Red);
}
/// <summary>
/// destructor
/// </summary>
Bullet::~Bullet() {}

/// <summary>
/// Update loop
/// </summary>
void Bullet::update()
{
	timer = lifeClock.getElapsedTime();
	float BulletX = m_sprite.getPosition().x + cos(m_sprite.getRotation()*(acos(-1) / 180)) * SPEED;
	float BulletY = m_sprite.getPosition().y + sin(m_sprite.getRotation()*(acos(-1) / 180)) * SPEED;
	m_sprite.setPosition(BulletX, BulletY);
	m_collisionCircle.setPosition(BulletX, BulletY);
	if (timer.asSeconds() > 2.f)
	{
		m_isAlive = false;
	}
}

/// <summary>
/// Draw loop
/// </summary>
/// <param name="window">Window to draw sprite</param>
void Bullet::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

/// <summary>
/// Returns the bullets alive state
/// </summary>
/// <returns>bool for if alive or not</returns>
bool Bullet::isAlive()
{
	return m_isAlive;
}

/// <summary>
/// Get the collision circle
/// </summary>
/// <returns>the collision circle</returns>
sf::CircleShape Bullet::getCollisionCircle()
{
	return m_collisionCircle;
}

/// <summary>
/// Set whether the bullet is alive or not
/// </summary>
/// <param name="status">the bool for alive or dead</param>
void Bullet::setAliveStatus(bool status)
{
	m_isAlive = status;
}
