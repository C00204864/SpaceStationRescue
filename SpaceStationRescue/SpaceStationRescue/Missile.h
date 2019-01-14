#ifndef MISSILE_H
#define MISSILE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Missile {

public:
	Missile(sf::Sprite nestSprite);
	~Missile();

	void update(sf::Sprite sprite);
	void draw(sf::RenderWindow & window);
	bool isAlive();

	void seek(sf::Vector2f pos);

private:
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;

	sf::Clock lifeClock;
	sf::Time timer;

	float rotation;
};

#endif // !MISSILE_H

