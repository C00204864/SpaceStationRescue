#ifndef BULLET_H
#define BULLET_H

#include<iostream>
#include<SFML/Graphics.hpp>

class Bullet {
public:
	Bullet(sf::Sprite sprite);
	~Bullet();
	void update();
	void draw(sf::RenderWindow & window);
	bool isAlive();
private:
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;

	sf::Clock lifeClock;
	sf::Time timer;
};


#endif // !BULLET_H
