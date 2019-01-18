#ifndef SWEEPER_H
#define SWEEPER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Worker.h"
#include "MathUtil.h"

class Sweeper
{
public:
	Sweeper(sf::Vector2f pos, Player & player, std::vector<Worker *> & workers);
	~Sweeper();
	void update(float dt);
	void render(sf::RenderWindow & window);
	bool isAlive();
	sf::Vector2f getPosition();
	void checkCollision(sf::FloatRect tileRect);
private:
	void seek(sf::Vector2f pos);
	Player & m_refPlayer;
	std::vector<Worker *> & m_refWorkers;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_collisionCircle;
	bool m_alive;
	float m_rotation;
	sf::Vector2f m_targetPosition;
	const float COLLISION_RADIUS = 20.f;
	const float MAX_ROTATION = 3.5f;
	const float MAX_SPEED = 2.5f;
	const float SEEK_DISTANCE = 1200.f;
	const float SEEK_THRESHOLD = 20.f;
	const float ENTITY_DISTANCE_THRESHOLD = 200.f;
	float timer;
	int workerCount;
};

#endif // !SWEEPER_H