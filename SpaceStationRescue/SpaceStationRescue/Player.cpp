#include "Player.h"
/// <summary>
/// Entity the user controls 
/// </summary>
/// <param name="pos"> Spawn Position for the player</param>
Player::Player(sf::Vector2f pos)
{
	m_startPos = pos;
	position = pos;
	speed = 0;
	if (!texture.loadFromFile("Assets\\Images\\PlayerShip.png"))
	{
		std::cout << "Error: Could not load player sprite" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setRotation(0);
	sprite.setScale(0.15, 0.15);

	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	m_collisionCircle.setRadius(sqrt((spriteBounds.width / 2.f) * (spriteBounds.width / 2.f) + (spriteBounds.height / 2.f) * (spriteBounds.height / 2.f)));

	rotation = 0;
	orientation = 0;

	m_collisionCircle.setFillColor(sf::Color(125, 125, 125, 125));
	m_collisionCircle.setOrigin(m_collisionCircle.getRadius(), m_collisionCircle.getRadius());
	m_shieldActive = false;

	m_shieldShape.setRadius(m_collisionCircle.getRadius());
	m_shieldShape.setFillColor(sf::Color(0, 0, 255, 125));
	m_shieldShape.setOutlineThickness(2);
	m_shieldShape.setOutlineColor(sf::Color(255,0,255,125));
	m_shieldShape.setOrigin(m_collisionCircle.getOrigin());
	m_shieldShape.setPosition(sprite.getPosition());

	maxSpeed = 5;

	m_health = 100;
	m_amountOfWorkers = 0;
}
/// <summary>
/// Destructor
/// </summary>
Player::~Player()
{
}

/// <summary>
/// Draw function for the player and its shield powerup
/// </summary>
/// <param name="window">RenderWindow for drawing to the screen</param>
void Player::render(sf::RenderWindow & window)
{
	for (auto b : m_bullets)
	{
		b->draw(window);
	}
	window.draw(sprite);
	if (m_shieldActive)
	{
		window.draw(m_shieldShape);
	}
}

/// <summary>
/// Update loop for the player
/// </summary>
/// <param name="dt">Deltatime</param>
void Player::update(sf::Time dt)
{
	m_lastPosition = sprite.getPosition();

	sprite.setPosition((sprite.getPosition().x + cos(rotation*(acos(-1) / 180)) * speed), (sprite.getPosition().y + sin(rotation*(acos(-1) / 180)) * speed));
	m_collisionCircle.setPosition(sprite.getPosition());
	sprite.setRotation(rotation);

	for (auto b : m_bullets)
	{
		b->update();
	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets.at(i)->isAlive() == false)
		{
			m_bullets.at(i)->~Bullet();
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	if (m_shieldActive)
	{
		m_shieldTime = m_shieldClock.getElapsedTime();

		if (m_shieldTime.asSeconds() > 15)
		{
			m_shieldClock.restart();
			m_shieldActive = false;
		}
	}

	if (m_speedBoostActive)
	{
		m_speedTime = m_speedClock.getElapsedTime();

		if (m_speedTime.asSeconds() > 15)
		{
			m_speedClock.restart();
			m_speedBoostActive = false;
			maxSpeed = 5;



			if (speed > maxSpeed)
			{
				speed = maxSpeed;
			}
			else if (-speed < -maxSpeed)
			{
				speed = maxSpeed;
			}
		}
	}

	m_shieldShape.setPosition(sprite.getPosition());
}
/// <summary>
/// Circle for collision
/// </summary>
/// <returns>Collision Circle</returns>
sf::CircleShape Player::getCollisionCircle()
{
	return m_collisionCircle;
}

/// <summary>
/// Check the collision with a map tile
/// </summary>
/// <param name="tileRect">Tile to be checked</param>
void Player::checkCollision(sf::FloatRect tileRect)
{
	if (checkCircleRectangleCollision(m_collisionCircle, tileRect))
	{
		sf::Vector2f currentPosition = sprite.getPosition();
		sf::Vector2f floatRectCenter = getFloatRectCenter(tileRect);
		sf::Vector2f between = currentPosition - floatRectCenter;
		if (abs(between.x) > abs(between.y))
		{
			between.y = 0;
		}
		else
		{
			between.x = 0;
		}
		currentPosition -= between;
		between = setVecSize(between, tileRect.width / 2.f + m_collisionCircle.getRadius());
		currentPosition += between;
		m_collisionCircle.setPosition(currentPosition);
		m_shieldShape.setPosition(currentPosition);
		sprite.setPosition(currentPosition);
	}
}

/// <summary>
/// Increase the players rotation
/// </summary>
void Player::increaseRotation()
{
	rotation += 5;
	if (rotation >= 360)
	{
		rotation = 0;
	}
}

/// <summary>
/// Decrease the players rotation
/// </summary>
void Player::decreaseRotation()
{
	rotation -= 5;
	if (rotation <= 0)
	{
		rotation = 359;
	}
}

/// <summary>
/// Set the speed value for the player
/// </summary>
/// <param name="s">The value to set speed to</param>
void Player::SetSpeed(float s)
{
	speed = s;
}

/// <summary>
/// Increase the player speed
/// </summary>
void Player::IncreaseSpeed()
{
	if (speed < maxSpeed)
	{
		speed += 0.1;
	}
}

/// <summary>
/// Decrease the player speed
/// </summary>
void Player::DecreaseSpeed()
{
	if (speed > -maxSpeed)
	{
		speed -= 0.1;
	}
}

/// <summary>
/// Get the current position of the player
/// </summary>
/// <returns>the position of the player</returns>
sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

/// <summary>
/// Get the current speed of the player
/// </summary>
/// <returns>The speed of the player</returns>
float Player::getSpeed()
{
	return speed;
}

/// <summary>
/// Get the current rotation of the player
/// </summary>
/// <returns></returns>
float Player::getRotation()
{
	return rotation;
}

/// <summary>
/// Create a new bullet and add it to the bullet vector
/// </summary>
void Player::SpawnBullet()
{
	m_bullets.push_back(new Bullet(sprite.getPosition(), sprite.getRotation()));
}

void Player::updateWorkers(int amount)
{
	m_amountOfWorkers += amount;
	if (m_amountOfWorkers < 0)
	{
		m_amountOfWorkers = 0;
	}
}

/// <summary>
/// Get the player sprite object
/// </summary>
/// <returns>The sprite of the player</returns>
sf::Sprite & Player::getSprite()
{
	return sprite;
}

/// <summary>
/// Activate the shield powerup
/// </summary>
void Player::activateShield()
{
	if (m_shieldActive == false)
	{
		m_shieldClock.restart();
		m_shieldActive = true;
	}
	else
	{
		m_shieldClock.restart();
	}
}

/// <summary>
/// Activate the speed boost powerup
/// </summary>
void Player::activateSpeedBoost()
{
	if (m_speedBoostActive == false)
	{
		m_speedClock.restart();
		m_speedBoostActive = true;
		maxSpeed = 10;
	}
	else
	{
		m_speedClock.restart();
	}
	
}

/// <summary>
/// Get the players current health
/// </summary>
/// <returns>The health of the player</returns>
int Player::getHealth()
{
	return m_health;
}

/// <summary>
/// Get the current amount of workers the player has
/// </summary>
/// <returns>The number of workers</returns>
int Player::getWorkersAmount()
{
	return m_amountOfWorkers;
}

/// <summary>
/// Update the current health value of the player
/// </summary>
/// <param name="amount">The amount of health to be added or taken away</param>
void Player::updateHealth(int amount)
{
	m_health += amount;
	if (m_health < 0)
	{
		m_health = 0;
	}
}

/// <summary>
/// Get the bullet vector
/// </summary>
/// <returns>The vector of bullets</returns>
std::vector<Bullet *> & Player::getBullets()
{
	return m_bullets;
}

void Player::reset()
{
	m_health = 100;
	m_amountOfWorkers = 0;
	sprite.setPosition(m_startPos);
	m_shieldActive = false;
	m_speedBoostActive = false;
	m_shieldClock.restart();
	m_speedClock.restart();
}