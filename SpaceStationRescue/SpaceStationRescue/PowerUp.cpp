#include "PowerUp.h"
/// <summary>
/// PowerUp constructor
/// </summary>
/// <param name="position">Position to spawn at</param>
/// <param name="type">type of powerup to spawn as</param>
PowerUp::PowerUp(sf::Vector2f position, PowerType type)
{
	
	
	m_sprite.setPosition(position);
	m_type = type;

	if (m_type == PowerType::SHIELD)
	{
		if (!m_texture.loadFromFile("Assets\\Images\\shield.png"))
		{
			std::cout << "Failed to load shield texture" << std::endl;
		}

		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(0.3, 0.3);
	}
	else
	{
		if (!m_texture.loadFromFile("Assets\\Images\\speed.png"))
		{
			std::cout << "Failed to load shield texture" << std::endl;
		}

		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		m_sprite.setScale(0.2, 0.2);
	}


	m_isAlive = true;
}

/// <summary>
/// destructor
/// </summary>
PowerUp::~PowerUp()
{
}

/// <summary>
/// Update loop for powerup
/// </summary>
void PowerUp::update()
{
	m_sprite.setRotation(m_sprite.getRotation() + 1);
}

/// <summary>
/// Draw loop for the Powerup
/// </summary>
/// <param name="window">Window for drawing the powerup</param>
void PowerUp::draw(sf::RenderWindow & window)
{
	if (m_isAlive)
	{
		window.draw(m_sprite);
	}	
}

/// <summary>
/// Check the collision of the parameter sprite
/// </summary>
/// <param name="sprite">Sprite to check</param>
/// <returns>bool for if a collision happened</returns>
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

/// <summary>
/// Alive status for powerup
/// </summary>
/// <param name="b">bool for if alive or not</param>
void PowerUp::setAlive(bool b)
{
	m_isAlive = b;
}

/// <summary>
/// Get the Type of the powerup
/// </summary>
/// <returns>The type of the powerup</returns>
PowerType PowerUp::getType()
{
	return m_type;
}
