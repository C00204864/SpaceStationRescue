#include "Player.h"

Player::Player(sf::Vector2f pos)
{
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
	sprite.setScale(0.2, 0.2);

	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	m_collisionCircle.setRadius(sqrt((spriteBounds.width / 2.f) * (spriteBounds.width / 2.f) + (spriteBounds.height / 2.f) * (spriteBounds.height / 2.f)));

	rotation = 0;
	orientation = 0;

	m_collisionCircle.setFillColor(sf::Color(125, 125, 125, 125));
	m_collisionCircle.setOrigin(m_collisionCircle.getRadius(), m_collisionCircle.getRadius());

	activateShield = false;


	m_shieldShape.setRadius(50);
	m_shieldShape.setFillColor(sf::Color(0, 0, 255, 125));
	m_shieldShape.setOutlineThickness(2);
	m_shieldShape.setOutlineColor(sf::Color(255,0,255,125));
	m_shieldShape.setOrigin(m_shieldShape.getGlobalBounds().width / 2, m_shieldShape.getGlobalBounds().height / 2);
	m_shieldShape.setPosition(sprite.getPosition());

	maxSpeed = 5;
	
}

Player::~Player()
{
}

void Player::render(sf::RenderWindow & window)
{
	for (auto b : m_bullets)
	{
		b->draw(window);
	}

	window.draw(m_collisionCircle);

	window.draw(sprite);

	if (activateShield)
	{
		window.draw(m_shieldShape);
	}
	
}

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



	if (activateShield)
	{
		m_shieldTime = m_shieldClock.getElapsedTime();

		if (m_shieldTime.asSeconds() > 15)
		{
			m_shieldClock.restart();
			activateShield = false;
		}
	}



	//std::cout << "Speed Time: " << m_speedTime.asSeconds() << std::endl;
	if (activateSpeedBoost)
	{
		m_speedTime = m_speedClock.getElapsedTime();

		if (m_speedTime.asSeconds() > 15)
		{
			m_speedClock.restart();
			activateSpeedBoost = false;
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
		sprite.setPosition(currentPosition);
	}
}


void Player::increaseRotation()
{
	rotation += 5;
	if (rotation >= 360)
	{
		rotation = 0;
	}
}

void Player::decreaseRotation()
{
	rotation -= 5;
	if (rotation <= 0)
	{
		rotation = 359;
	}
}

void Player::SetSpeed(float s)
{
	speed = s;
}

void Player::IncreaseSpeed()
{
	if (speed < maxSpeed)
	{
		speed += 0.1;
	}
}

void Player::DecreaseSpeed()
{
	if (speed > -maxSpeed)
	{
		speed -= 0.1;
	}
}

sf::Vector2f Player::getPosition()
{
	return sprite.getPosition();
}

float Player::getSpeed()
{
	return speed;
}

float Player::getRotation()
{
	return rotation;
}

void Player::SpawnBullet()
{
	m_bullets.push_back(new Bullet(sprite));
}

sf::Sprite & Player::getSprite()
{
	return sprite;
}

void Player::activateTheShield()
{
	if (activateShield == false)
	{
		m_shieldClock.restart();
		activateShield = true;
	}
	else
	{
		m_shieldClock.restart();
	}
}

void Player::activateTheSpeedBoost()
{
	if (activateSpeedBoost == false)
	{
		m_speedClock.restart();
		activateSpeedBoost = true;
		maxSpeed = 20;
	}
	else
	{
		m_speedClock.restart();
	}
	
}
