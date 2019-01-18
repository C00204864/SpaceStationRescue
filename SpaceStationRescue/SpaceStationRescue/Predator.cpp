#include "Predator.h"

Predator::Predator(World * world, Player & player) : p_world(world), m_isAlive(false), m_refPlayer(player)
{
	if (!m_texture.loadFromFile("Assets\\Images\\Predator.png"))
	{
		std::cout << "Error: Could not load predator texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setRotation(0);
	m_sprite.setScale(0.06, 0.06);
	sf::FloatRect spriteBounds = m_sprite.getGlobalBounds();
	m_collisionCircle.setRadius(sqrt((spriteBounds.width / 2.f) * (spriteBounds.width / 2.f) + (spriteBounds.height / 2.f) * (spriteBounds.height / 2.f)));
	m_collisionCircle.setFillColor(sf::Color(255, 0, 0, 125));
	m_collisionCircle.setOrigin(m_collisionCircle.getRadius(), m_collisionCircle.getRadius());

	if (!m_explosion.loadFromFile("Assets\\Images\\Explosion.png"))
	{
		std::cout << "Error: Could not load explosion texture" << std::endl;
	}
	m_animation = new Animation(&m_explosion, sf::Vector2u(14, 1), 0.05f);
	m_animation->PlayAnimationOnce(true);
	m_animating = false;
	

	rect = m_sprite.getTextureRect();
}

Predator::~Predator() {}

void Predator::reset(sf::Vector2f positionIn)
{
	m_isAlive = true;
	m_animating = false;
	m_animation->reset();
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setTextureRect(rect);
	m_sprite.setRotation(0);
	m_sprite.setScale(0.06, 0.06);
	m_sprite.setPosition(positionIn);
	Tile * nextTile = p_world->getTilePointer(positionIn.x / p_world->getTileWidth(), positionIn.y / p_world->getTileWidth());
	if (nullptr != nextTile)
	{
		targetTile = nextTile;
	}
}

void Predator::explode()
{
	//m_isAlive = false;
	m_animating = true;
}

void Predator::update(float dt)
{
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

	if (m_animating)
	{
		if (m_animation->isAnimFinished())
		{
			m_animating = false;
			m_isAlive = false;
		}
		m_animation->update(0, dt);
		m_sprite.setScale(1, 1);
		m_sprite.setTexture(m_explosion);
		m_sprite.setTextureRect(m_animation->uvRect);
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f);
	}

	if (m_isAlive && !m_animating)
	{
		sf::Vector2f position = m_sprite.getPosition();
		sf::Vector2f playerPos = m_refPlayer.getPosition();
		if (getDistance(playerPos, m_sprite.getPosition()) < PLAYER_DISTANCE_THRESHOLD)
		{
			bulletTimer += dt;
			seek(playerPos);
			if (bulletTimer > TIME_BETWEEN_SHOTS)
			{
				m_bullets.push_back(new Bullet(m_sprite.getPosition(), m_sprite.getRotation()));
				bulletTimer = 0.f;
			}
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

		// Check Collisions with the player and player bullets
		if(checkCircleCollision(m_collisionCircle, m_refPlayer.getCollisionCircle()))
		{
			m_refPlayer.updateHealth(-10);
			explode();
		}
		for (auto & bullet : m_refPlayer.getBullets())
		{
			if (checkCircleCollision(m_collisionCircle, bullet->getCollisionCircle()))
			{
				explode();
				bullet->setAliveStatus(false);
			}
		}
		for (auto & bullet : m_bullets)
		{
			if (checkCircleCollision(m_refPlayer.getCollisionCircle(), bullet->getCollisionCircle()))
			{
				m_refPlayer.updateHealth(-5);
				bullet->setAliveStatus(false);
			}
		}
	}
}

void Predator::render(sf::RenderWindow & window)
{
	for (auto b : m_bullets)
	{
		b->draw(window);
	}
	if (m_isAlive)
	{
		//window.draw(m_collisionCircle);
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
	float orientation = m_sprite.getRotation();
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
		float absX = abs(between.x);
		float absY = abs(between.y);

		if (absX > absY + 0.1f)
		{
			between.y = 0;
		}
		else if(absX + 0.1f < absY )
		{
			between.x = 0;
		}
		else
		{
			currentPosition -= between;
			between = setVecSize(between, sqrt(2 * (tileRect.width * tileRect.width)));
			currentPosition += between;
			return;
		}
		currentPosition -= between;
		between = setVecSize(between, tileRect.width / 2.f + m_collisionCircle.getRadius());
		currentPosition += between;
		m_collisionCircle.setPosition(currentPosition);
		m_sprite.setPosition(currentPosition);
	}
}

