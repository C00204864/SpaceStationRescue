#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include<vector>
#include"Bullet.h"

class Player {
public:
	Player(sf::Vector2f pos);
	~Player();
	void render(sf::RenderWindow &window);
	void update(sf::Time dt);

	void increaseRotation();
	void decreaseRotation();
	void SetSpeed(float s);

	void IncreaseSpeed();
	void DecreaseSpeed();

	sf::Vector2f getPosition();
	float getSpeed();
	float getRotation();

	void SpawnBullet();

private:
	sf::Vector2f position;
	float speed;

	sf::Vector2f velocity;
	sf::Texture texture;
	sf::Sprite sprite;
	float rotation;
	float orientation;

	std::vector<Bullet *> m_bullets;

};

#endif // !PLAYER_H

