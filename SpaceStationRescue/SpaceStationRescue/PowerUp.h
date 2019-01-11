#ifndef POWERUP_H
#define POWERUP_H

#include<iostream>
#include<SFML/Graphics.hpp>

enum PowerType
{
	SHIELD,
	SPEED
};

class PowerUp {
public:
	PowerUp(sf::Vector2f position);
	~PowerUp();
	void update();
	void draw(sf::RenderWindow & window);
	bool collisionCheck(sf::Sprite sprite);
	void setAlive(bool b);
private:
	bool m_isAlive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	PowerType m_type;

};

#endif // !POWERUP_H

