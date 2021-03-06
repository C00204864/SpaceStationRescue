#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "World.h"
#include "PowerUp.h"
#include "Nest.h"
#include "Missile.h"
#include "Worker.h"

#include "MainMenuScreen.h"

#include "Hud.h"
#include "DieScreen.h"
#include"WinScreen.h"

class Menu;
class DieScreen;
class WinScreen;

enum State{
	MAINMENU,
	PLAY,
	DIE,
	WIN
};

class Game
{
public:
	// Public Methods
	Game();
	~Game();
	void run();
	void setGameState(State state);
	void endGame();
	void reset();
private:
	// Private Methods
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	// Private Members
	sf::RenderWindow m_window; // main SFML window
	sf::View m_mainView;
	sf::View m_miniMapView;
	bool m_exitGame; // control exiting game
	Player m_player;
	World m_world;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::Texture m_minimapTexture;
	sf::Sprite m_minimapBackground;


	sf::Texture m_emptyShaderTexture;
	sf::Sprite m_emptyShaderSprite;
	sf::Shader m_shader;

	float timeCounter;

	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;


	sf::Clock bulletClock;
	sf::Time timeElapsed;

	std::vector<PowerUp *> powerUps;

	State m_state;

	Menu * menu;

	Hud * hud;

	DieScreen * dieScreen;

	WinScreen * winScreen;


};

#endif // !GAME_H