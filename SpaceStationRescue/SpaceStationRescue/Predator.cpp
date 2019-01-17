#include "Predator.h"

Predator::Predator(World * world, Player & player) : p_world(world), m_isAlive(false), m_refPlayer(player)
{
	if (!m_texture.loadFromFile("Assets\\Images\\PlayerShip.png"))
	{
		std::cout << "Error: Could not load predator texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setRotation(0);
	m_sprite.setScale(0.2, 0.2);

	sf::FloatRect spriteBounds = m_sprite.getGlobalBounds();
	m_collisionCircle.setRadius(sqrt((spriteBounds.width / 2.f) * (spriteBounds.width / 2.f) + (spriteBounds.height / 2.f) * (spriteBounds.height / 2.f)));
	m_collisionCircle.setFillColor(sf::Color(255, 0, 0, 125));
	m_collisionCircle.setOrigin(m_collisionCircle.getRadius(), m_collisionCircle.getRadius());
}

Predator::~Predator()
{
}

void Predator::reset(sf::Vector2f positionIn)
{
	m_isAlive = true;
	m_sprite.setPosition(positionIn);
	Tile * nextTile = p_world->getTilePointer(positionIn.x / p_world->getTileWidth(), positionIn.y / p_world->getTileWidth());
	if (nullptr != nextTile)
	{
		targetTile = nextTile;
	}
}

void Predator::explode()
{
	m_isAlive = false;
}

void Predator::update(float dt)
{
	if (m_isAlive)
	{
		sf::Vector2f position = m_sprite.getPosition();
		sf::Vector2f playerPos = m_refPlayer.getPosition();
		if (getDistance(playerPos, m_sprite.getPosition()) < PLAYER_DISTANCE_THRESHOLD)
		{
			seek(playerPos);
			Tile * nextTile = p_world->getTilePointer(position.x / p_world->getTileWidth(), position.y / p_world->getTileWidth());
			if (nullptr != nextTile)
			{
				targetTile = nextTile;
			}
		}
		else
		{
			if (nullptr == targetTile)
			{
				std::cout << "Error" << std::endl;
			}
			sf::Vector2f targetPos = targetTile->getCenterPosition();
			seek(targetPos);
			if (getDistance(m_sprite.getPosition(), targetPos) < TILE_DISTANCE_THRESHOLD)
			{
				targetTile = targetTile->getNext();
			}
		}
	}
}

void Predator::render(sf::RenderWindow & window)
{
	if (m_isAlive)
	{
		window.draw(m_collisionCircle);
		window.draw(m_sprite);
	}
}

bool Predator::isAlive()
{
	return m_isAlive;
}

void Predator::seek(sf::Vector2f targetPosition)
{
	sf::Vector2f position = m_sprite.getPosition();
	sf::Vector2f vectorBetween = targetPosition - position;
	float orientation = m_sprite.getRotation();// / 180.f * acos(-1);
	if (orientation < 0)
	{
		orientation += 360.f;
	}
	float desiredOrientationDegrees = atan2(vectorBetween.y, vectorBetween.x) * 180.f / acos(-1);
	if (desiredOrientationDegrees < 0)
	{
		desiredOrientationDegrees += 360.f;
	}
	float requiredRotation = orientation - desiredOrientationDegrees;
	if (requiredRotation > 180)
	{
		requiredRotation -= 360.f;
	}
	else if (requiredRotation < -180.f)
	{
		requiredRotation += 360.f;
	}
	if (requiredRotation < MAX_ROTATION && requiredRotation > -MAX_ROTATION)
	{
		orientation = desiredOrientationDegrees;
	}
	else
	{
		orientation += requiredRotation < 0 ? MAX_ROTATION : -MAX_ROTATION;
	}
	m_sprite.setRotation(orientation);
	m_sprite.setPosition((m_sprite.getPosition().x + cos(orientation*(acos(-1) / 180))* 3.5f), (m_sprite.getPosition().y + sin(orientation*(acos(-1) / 180)) * 3.5f));
	m_collisionCircle.setPosition(m_sprite.getPosition());
}

sf::Vector2f Predator::getPosition()
{
	return m_sprite.getPosition();
}

void Predator::checkCollision(sf::FloatRect tileRect)
{
	if (checkCircleRectangleCollision(m_collisionCircle, tileRect))
	{
		sf::Vector2f currentPosition = m_sprite.getPosition();
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
		m_sprite.setPosition(currentPosition);
	}
}

