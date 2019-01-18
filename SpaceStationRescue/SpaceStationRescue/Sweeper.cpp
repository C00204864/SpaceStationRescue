#include "Sweeper.h"

Sweeper::Sweeper(sf::Vector2f pos, Player & player, std::vector<Worker *> & workers) : m_refPlayer(player), m_refWorkers(workers), timer(0.f), workerCount(0)
{
	if (!m_texture.loadFromFile("Assets\\Images\\Sweeper.png"))
	{
		std::cout << "Error: Could not load worker texture" << std::endl;
	}
	m_rotation = 0;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
	m_sprite.setRotation(m_rotation);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(0.15, 0.15);
	m_collisionCircle.setRadius(COLLISION_RADIUS);
	m_collisionCircle.setOrigin(COLLISION_RADIUS, COLLISION_RADIUS);
	m_collisionCircle.setPosition(pos);
	m_alive = true;
	float randRotation = rand() % 360 - 180;
	m_targetPosition.x = cos(randRotation / 180.f * acos(-1)) * SEEK_DISTANCE;
	m_targetPosition.y = sin(randRotation / 180.f * acos(-1)) * SEEK_DISTANCE;
	m_targetPosition += pos;


	if (!m_explosion.loadFromFile("Assets\\Images\\Explosion.png"))
	{
		std::cout << "Error: Could not load explosion texture" << std::endl;
	}
	m_animation = new Animation(&m_explosion, sf::Vector2u(14, 1), 0.05f);
	m_animation->PlayAnimationOnce(true);
	m_animating = false;


	rect = m_sprite.getTextureRect();
}

Sweeper::~Sweeper() {}

void Sweeper::update(float dt)
{
	timer += dt;
	if (timer > 3.5f || getDistance(m_targetPosition, m_sprite.getPosition()) < SEEK_THRESHOLD)
	{
		float randRotation = rand() % 360 - 180;
		m_targetPosition.x = cos(randRotation / 180.f * acos(-1)) * SEEK_DISTANCE;
		m_targetPosition.y = sin(randRotation / 180.f * acos(-1)) * SEEK_DISTANCE;
		m_targetPosition += m_sprite.getPosition();
		timer = 0.f;
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

	if (m_alive || !m_animating)
	{
		sf::Vector2f pos = m_sprite.getPosition();
		sf::Vector2f playerPos = m_refPlayer.getPosition();
		if (getDistance(playerPos, pos) < ENTITY_DISTANCE_THRESHOLD)
		{
			seek(pos + (pos - playerPos));
		}
		else
		{
			bool wander = true;
			for (auto & worker : m_refWorkers)
			{
				sf::Vector2f workerPos = worker->getPosition();
				if (getDistance(workerPos, pos) < ENTITY_DISTANCE_THRESHOLD && worker->isAlive())
				{
					wander = false;
					seek(pos + (workerPos - pos));
					break;
				}
			}
			if (wander)
			{
				seek(m_targetPosition);
			}
		}
		if (checkCircleCollision(m_collisionCircle, m_refPlayer.getCollisionCircle()))
		{
			m_refPlayer.updateWorkers(workerCount);
			//m_alive = false;
			m_animating = true;
			m_refPlayer.updateHealth(-5);

		}
		for (auto & bullet : m_refPlayer.getBullets())
		{
			if (checkCircleCollision(m_collisionCircle, bullet->getCollisionCircle()))
			{
				m_refPlayer.updateWorkers(workerCount);
				//m_alive = false;
				m_animating = true;
			}
		}
		for (auto & worker : m_refWorkers)
		{
			if (worker->isAlive() && checkCircleCollision(worker->getCollisionCircle(), m_collisionCircle))
			{
				++workerCount;
				worker->setAliveStatus(false);
			}
		}
	}

}

void Sweeper::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_sprite);
	}
}

bool Sweeper::isAlive()
{
	return m_alive;
}

void Sweeper::seek(sf::Vector2f targetPosition)
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
	m_sprite.setPosition((m_sprite.getPosition().x + cos(orientation*(acos(-1) / 180))* MAX_SPEED), (m_sprite.getPosition().y + sin(orientation*(acos(-1) / 180)) *MAX_SPEED));
	m_collisionCircle.setPosition(m_sprite.getPosition());
}

sf::Vector2f Sweeper::getPosition()
{
	return m_sprite.getPosition();
}

void Sweeper::checkCollision(sf::FloatRect tileRect)
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