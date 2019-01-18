#ifndef MISSILE_H
#define MISSILE_H

// STD Includes
#include <iostream>

// SFML Includes
#include <SFML/Graphics.hpp>

// Project Includes
#include "Player.h"

class Missile {

public:
	Missile(Player & player);
	~Missile();
	void reset(sf::Vector2f positionIn, float rotationIn);
	void explode();
	void update();
	void render(sf::RenderWindow & window);
	bool isAlive();
	void setAliveStatus(bool status);
	sf::CircleShape getCollisionCircle();

private:
	// Private Methods
	void seek(sf::Vector2f pos);

	// Private Members
	Player & m_refPlayer;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_collisionCircle;
	sf::Vector2f m_velocity;
	sf::Clock lifeClock;
	bool m_isAlive;
	float rotation;
	const float HIT_RADIUS = 15.f;
};

#endif // !MISSILE_H

