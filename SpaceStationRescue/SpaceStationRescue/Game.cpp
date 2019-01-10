#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32 }, "Space Station Rescue" },
	m_exitGame{ false }, // When true game will exit
	m_player{sf::Vector2f(400,400)},
	m_world{"Assets\\Levels\\Level.txt", 96, 96, m_player }
{
	// Views
	m_mainView = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	m_miniMapView = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	m_miniMapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	m_miniMapView.zoom(5.f);
	m_window.setView(m_mainView);

	// Background and Shader
	if (!m_backgroundTexture.loadFromFile("Assets\\Images\\Background.png"))
	{
		std::cout << "Error: Could not load background texture." << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	sf::FloatRect backgroundLocalBounds = m_backgroundSprite.getLocalBounds();
	m_backgroundSprite.setScale(SCREEN_WIDTH / backgroundLocalBounds.width, SCREEN_HEIGHT / backgroundLocalBounds.height);
}


Game::~Game() {}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 960 fps
	while (m_window.isOpen())
	{
		processEvents(); // As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // At least 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // As many as possible
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	else if (m_window.hasFocus()) // Ensure window is in focus before any action is taken
	{
		m_player.update(t_deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_player.increaseRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_player.decreaseRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_player.DecreaseSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_player.IncreaseSpeed();
		}
		sf::Vector2f playerPos = m_player.getPosition();
		m_mainView.setCenter(playerPos);
		m_backgroundSprite.setPosition(playerPos.x - SCREEN_WIDTH / 2.f, playerPos.y - SCREEN_HEIGHT / 2.f);
	}
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw Main Game
	m_window.setView(m_mainView);
	m_window.draw(m_backgroundSprite);
	m_world.render(m_window);
	m_player.render(m_window);

	// Draw MiniMap
	m_window.setView(m_miniMapView);
	m_world.render(m_window);
	m_player.render(m_window);

	m_window.display();
}
