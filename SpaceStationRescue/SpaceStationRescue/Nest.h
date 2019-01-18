#ifndef NEST_H
#define NEST_H

// Predefinition to deal woth circular references
class World;

// STD Inlcudes
#include <iostream>

// SFML Includes
#include <SFML/Graphics.hpp>

// Project Includes
#include "Player.h"
#include "Missile.h"
#include "World.h"
#include "Predator.h"
#include "MathUtil.h"
#include "Animation.h"

class Nest
{
public:
	Nest(sf::Vector2f pos, Player & player, World * world);
	~Nest();
	void update(float dt);
	void render(sf::RenderWindow & m_window);
	sf::Sprite getSprite();
	std::vector<Predator *> & getPredatorVector();
	bool isAlive();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_circle;
	sf::CircleShape m_collisionCircle;
	Player & m_refPlayer;
	Missile * m_missile;
	std::vector<Predator *> m_predators;
	const int PREADTOR_COUNT = 2;
	float predatorSpawnSeconds;
	const float PREDATOR_SPAWN_TIME = 10.f;

	const float MISSILE_SPAWN_TIME = 3.5f;
	float missileSpawnSeconds;

	sf::Texture m_explosion;
	Animation * m_animation;
	bool m_animating;
	int m_health;
	bool m_alive;
};
#endif // !NEST_H

