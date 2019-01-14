#ifndef NEST_H
#define NEST_H

#include<SFML/Graphics.hpp>
#include"Player.h"
#include"Missile.h"
class Nest
{
public:
	Nest(sf::Vector2f pos, Player & player);
	~Nest();
	void update();
	void draw(sf::RenderWindow & m_window);
	void spawnNewPred();
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

