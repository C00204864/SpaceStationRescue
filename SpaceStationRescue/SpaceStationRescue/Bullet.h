#ifndef BULLET_H
#define BULLET_H

#include<iostream>
#include<SFML/Graphics.hpp>

class Bullet {
public:
	// Public Methods
	Bullet(sf::Vector2f position, float rotation);
	~Bullet();
	void update();
	void draw(sf::RenderWindow & window);
	bool isAlive();
	sf::CircleShape getCollisionCircle();
	void setAliveStatus(bool status);
private:
	// Private Members
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::CircleShape m_collisionCircle;
	sf::Vector2f m_velocity;
	sf::Clock lifeClock;
	sf::Time timer;
	const float RADIUS = 15.f;
	const float SPEED = 18.f;
};

#endif // !BULLET_H
