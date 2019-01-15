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

class Nest
{
public:
	Nest(sf::Vector2f pos, Player & player, World * world);
	~Nest();
	void update();
	void render(sf::RenderWindow & m_window);
	void spawnNewPredator();
	void spawnNewMissile();
	sf::Sprite getSprite();

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_circle;
	Player & m_refPlayer;
	//std::vector<Missile *> m_missiles;
	Missile * m_missile;
	std::vector<Predator *> m_predators;
	const int PREADTOR_COUNT = 2;
};
#endif // !NEST_H

