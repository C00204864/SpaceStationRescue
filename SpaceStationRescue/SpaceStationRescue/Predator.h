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

class Predator
{
public:
	Predator(World * world, sf::Vector2f positionIn);
	~Predator();
	void update(float dt);
	void render(sf::RenderWindow & window);
	bool isAlive();
	void seek(sf::Vector2f pos);
private:
	World * p_world;
	Tile * targetTile;
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;

	float rotation;

	float timer;
};

#endif // !PREADTOR_H
