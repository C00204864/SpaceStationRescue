#ifndef PLAYER_H
#define PLAYER_H

// STD Includes
#include <iostream>
#include <vector>

// SFML Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Project Includes
#include "Bullet.h"
#include "MathUtil.h"

class Player {
public:
	Player(sf::Vector2f pos);
	~Player();
	void render(sf::RenderWindow &window);
	void update(sf::Time dt);
	void checkCollision(sf::FloatRect tileRect);
	void increaseRotation();
	void decreaseRotation();
	void SetSpeed(float s);
	void IncreaseSpeed();
	void DecreaseSpeed();
	sf::Vector2f getPosition();
	float getSpeed();
	float getRotation();
	void SpawnBullet();
	sf::Sprite & getSprite();
	void activateTheShield();
	void activateTheSpeedBoost();

private:
	sf::Vector2f position;
	sf::Vector2f m_lastPosition;
	float speed;

	sf::Vector2f velocity;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::CircleShape m_collisionCircle;
	float rotation;
	float orientation;

	std::vector<Bullet *> m_bullets;

	sf::Clock m_shieldClock;
	sf::Time m_shieldTime;
	bool activateShield;

	sf::Clock m_speedClock;
	sf::Time m_speedTime;
	bool activateSpeedBoost;

	sf::CircleShape m_shieldShape;


	int maxSpeed;
};

#endif // !PLAYER_H

