#ifndef HUD_H
#define HUD_H


#include<SFML/Graphics.hpp>
#include "Player.h"

class Hud {
public:
	Hud(Player & p);
	~Hud();
	void update(sf::Vector2f trackPos);
	void draw(sf::RenderWindow & window);

private:
	Player & m_refPlayer;

	sf::Font m_font;
	sf::Text m_health;
	sf::Text m_workerAmount;

};

#endif // !HUD_H

