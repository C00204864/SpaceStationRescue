#ifndef PREDATOR_H
#define PREDATOR_H

// Predefinition to deal woth circular references
class World;

// STD Inlcudes
#include <iostream>

// SFML Includes
#include <SFML/Graphics.hpp>

// Project Includes
#include "World.h"
#include "Player.h"
#include "Bullet.h"

class Predator
{
public:
	Predator(World * world, Player & player);
	~Predator();
	void reset(sf::Vector2f position);
	void explode();
	void update(float dt);
	void render(sf::RenderWindow & window);
	bool isAlive();
	sf::Vector2f getPosition();
	void seek(sf::Vector2f pos);
	void checkCollision(sf::FloatRect tileRect);
private:
	World * p_world;
	Tile * targetTile;
	Player & m_refPlayer;
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_collisionCircle;
	sf::Vector2f m_velocity;
	std::vector<Bullet *> m_bullets;
	float rotation;
	float bulletTimer;
	const float MAX_SPEED = 5.f;
	const float MAX_ROTATION = 5.f;
	const float TILE_DISTANCE_THRESHOLD = 50.f;
	const float PLAYER_DISTANCE_THRESHOLD = 250.f;
	const float TIME_BETWEEN_SHOTS = 3.5f;
};

#endif // !PREADTOR_H
