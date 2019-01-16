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
	void seek(sf::Vector2f pos);
private:
	World * p_world;
	Tile * targetTile;
	Player & m_refPlayer;
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	float rotation;
	float timer;
};

#endif // !PREADTOR_H
