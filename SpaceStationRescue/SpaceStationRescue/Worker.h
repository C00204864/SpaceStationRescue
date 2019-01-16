#ifndef WORKER_H
#define WORKER_H

#include<SFML/Graphics.hpp>

class Worker
{
public:
	Worker(sf::Vector2f pos);
	~Worker();
	void update();
	void draw(sf::RenderWindow & window);

	void seek(sf::Vector2f pos);
	bool isAlive();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_alive;
	float m_rotation;

};

#endif // !WORKER_H

