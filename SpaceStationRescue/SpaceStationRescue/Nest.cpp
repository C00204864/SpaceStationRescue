#include "Nest.h"

/// <summary>
/// Nest object that spawns missiles and predators
/// </summary>
/// <param name="pos">Position to spawn at</param>
/// <param name="player">Ref to the player</param>
/// <param name="world">The world object</param>
Nest::Nest(sf::Vector2f pos, Player & player, World * world):
	m_refPlayer{player},
	m_health{4},
	m_alive{true}
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

	float collisionRadius = m_sprite.getGlobalBounds().width / 2.f;
	m_collisionCircle.setRadius(collisionRadius);
	m_collisionCircle.setOrigin(collisionRadius, collisionRadius);
	m_collisionCircle.setPosition(pos);

	// Setup Missiles and Predators
	m_missile = new Missile(m_refPlayer);
	for (int i = 0; i < PREADTOR_COUNT; ++i)
	{
		m_predators.push_back(new Predator(world, player));
	}

	if (!m_explosion.loadFromFile("Assets\\Images\\Explosion.png"))
	{
		std::cout << "Error: Could not load explosion texture" << std::endl;
	}
	m_animation = new Animation(&m_explosion, sf::Vector2u(14, 1), 0.05f);
	m_animation->PlayAnimationOnce(true);
	m_animating = false;
}

/// <summary>
/// Destructor for the nest
/// </summary>
Nest::~Nest() 
{
	delete m_animation;
	delete m_missile;
	for (int i = 0; i < m_predators.size(); ++i)
	{
		delete m_predators.at(i);
	}
}

/// <summary>
/// Update loop for the nest
/// </summary>
/// <param name="dt">Deltatime</param>
void Nest::update(float dt)
{
	m_missile->update();
	if (!m_missile->isAlive() && getDistance(m_refPlayer.getPosition(), m_sprite.getPosition()) < m_circle.getRadius())
	{
		missileSpawnSeconds += dt;
		if (m_alive && MISSILE_SPAWN_TIME < missileSpawnSeconds)
		{
			missileSpawnSeconds = 0;
			m_missile->reset(m_sprite.getPosition(), m_sprite.getRotation());
		}
	}

	for (auto & predator : m_predators)
	{
		if (m_alive && !predator->isAlive())
		{
			predatorSpawnSeconds += dt;
			if( PREDATOR_SPAWN_TIME < predatorSpawnSeconds)
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

	if (m_animating)
	{
		if (m_animation->isAnimFinished())
		{
			m_animating = false;
			m_alive = false;
		}
		m_animation->update(0, dt);
		m_sprite.setScale(1, 1);
		m_sprite.setTexture(m_explosion);
		m_sprite.setTextureRect(m_animation->uvRect);
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
	}

	if (m_alive)
	{
		// Check Collisions with the player and player bullets
		if (checkCircleCollision(m_collisionCircle, m_refPlayer.getCollisionCircle()))
		{
			m_refPlayer.updateHealth(-5);
		}
		if (m_missile->isAlive() && checkCircleCollision(m_missile->getCollisionCircle(), m_refPlayer.getCollisionCircle()))
		{
			m_missile->setAliveStatus(false);
			m_refPlayer.updateHealth(-5);
		}
		for (auto & bullet : m_refPlayer.getBullets())
		{
			if (checkCircleCollision(m_collisionCircle, bullet->getCollisionCircle()))
			{
				bullet->setAliveStatus(false);
				--m_health;
				if (0 == m_health)
				{
					//m_alive = false;
					m_animating = true;
				}
			}
		}
	}
}

/// <summary>
/// Draw loop for the Nest
/// </summary>
/// <param name="window">Window for drawing</param>
void Nest::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_circle);
		window.draw(m_sprite);
	}
	m_missile->render(window);
	for (auto & predator : m_predators)
	{
		predator->render(window);
	}
}

/// <summary>
/// Get the Sprite of the nest
/// </summary>
/// <returns>The sprite of the nest</returns>
sf::Sprite Nest::getSprite()
{
	return m_sprite;
}

/// <summary>
/// Get the vector of the predators
/// </summary>
/// <returns>The vector of predators</returns>
std::vector<Predator *> & Nest::getPredatorVector()
{
	return m_predators;
}
