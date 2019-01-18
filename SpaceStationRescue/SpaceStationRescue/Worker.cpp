#include "Worker.h"

Worker::Worker(sf::Vector2f pos, Player & player) : m_refPlayer(player), timer(0.f)
{
	if (!m_texture.loadFromFile("Assets\\Images\\worker.png"))
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
}

Worker::~Worker() {}

void Worker::update(float dt)
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
	if (m_alive)
	{
		seek(m_targetPosition);
		if (checkCircleCollision(m_collisionCircle, m_refPlayer.getCollisionCircle()))
		{
			m_refPlayer.updateWorkers(1);
			m_alive = false;
		}
	}

}

void Worker::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_sprite);
	}
}

bool Worker::isAlive()
{
	return m_alive;
}

void Worker::seek(sf::Vector2f targetPosition)
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

sf::Vector2f Worker::getPosition()
{
	return m_sprite.getPosition();
}

void Worker::setAliveStatus(bool status)
{
	m_alive = status;
}

sf::CircleShape Worker::getCollisionCircle()
{
	return m_collisionCircle;
}


void Worker::checkCollision(sf::FloatRect tileRect)
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