#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MathUtil.h"

class Worker
{
public:
	Worker(sf::Vector2f pos, Player & player);
	~Worker();
	void update(float dt);
	void render(sf::RenderWindow & window);
	bool isAlive();
	sf::Vector2f getPosition();
	void checkCollision(sf::FloatRect tileRect);
	void setAliveStatus(bool status);
	sf::CircleShape getCollisionCircle();
private:
	void seek(sf::Vector2f pos);
	Player & m_refPlayer;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_collisionCircle;
	bool m_alive;
	float m_rotation;
	sf::Vector2f m_targetPosition;
	const float COLLISION_RADIUS = 10.f;
	const float MAX_ROTATION = 2.5f;
	const float MAX_SPEED = 0.5f;
	const float SEEK_DISTANCE = 150.f;
	const float SEEK_THRESHOLD = 25.f;
	float timer;
};

#endif // !WORKER_H