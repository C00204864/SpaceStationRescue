#ifndef NEST_H
#define NEST_H

// STD Inlcudes
#include <iostream>

// SFML Includes
#include <SFML/Graphics.hpp>

// Project Includes
#include "Player.h"
#include "Missile.h"

class Nest
{
public:
	Nest(sf::Vector2f pos, Player & player);
	~Nest();
	void update();
	void draw(sf::RenderWindow & m_window);
	void spawnNewPredator();
	void spawnNewMissile();
	sf::Sprite getSprite();

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_circle;
	Player & m_player;
	std::vector<Missile *> m_missiles;
};
#endif // !NEST_H

