#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include"Player.h"
class Game
{
public:
	// Public Methods
	Game();
	~Game();
	void run();

private:
	// Private Methods
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	// Private Members
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game


	Player player;
};

#endif // !GAME_H