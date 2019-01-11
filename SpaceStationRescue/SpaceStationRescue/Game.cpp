#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 1280, 720, 32 }, "Space Station Rescue" },
	m_exitGame{ false }, // When true game will exit
	m_player{sf::Vector2f(400,400)},
	m_world{"Assets\\Levels\\Level.txt", 96, 96, m_player }
{
	// Views
	m_mainView = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	m_miniMapView = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	m_miniMapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	m_miniMapView.zoom(8.f);
	m_window.setView(m_mainView);

	// Background and Shader
	if (!m_backgroundTexture.loadFromFile("Assets\\Images\\Background.png"))
	{
		std::cout << "Error: Could not load background texture." << std::endl;
	}
	if (!m_emptyShaderTexture.loadFromFile("Assets\\Images\\Blank.png"))
	{
		std::cout << "Error: Could not load texture used for shader" << std::endl;
	}
	if (!m_shader.loadFromFile("Assets\\Shaders\\Stars.txt", sf::Shader::Fragment))
	{
		std::cout << "Error: Could not load shader" << std::endl;
	}
	m_shader.setUniform("resolution", sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	// Background
	m_backgroundSprite.setTexture(m_backgroundTexture);
	sf::FloatRect backgroundLocalBounds = m_backgroundSprite.getLocalBounds();
	m_backgroundSprite.setScale(1.f * SCREEN_WIDTH / backgroundLocalBounds.width, 1.f * SCREEN_HEIGHT / backgroundLocalBounds.height);

	// Shader
	m_emptyShaderSprite.setTexture(m_emptyShaderTexture);
	sf::FloatRect shaderLocalBounds = m_emptyShaderSprite.getLocalBounds();
	m_emptyShaderSprite.setScale(1.f * SCREEN_WIDTH / shaderLocalBounds.width, 1.f * SCREEN_HEIGHT / shaderLocalBounds.height);




	//powerups
	shield = new PowerUp(sf::Vector2f(500,500));

}


Game::~Game() {}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	//float timeCounter = 0.f;
	while (m_window.isOpen())
	{
		processEvents(); // As many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // At least 60 fps
			update(timePerFrame); // 60 fps
			timeCounter += timePerFrame.asSeconds();
			//std::cout << timeCounter << std::endl;
			m_shader.setUniform("time", timeCounter);
		}
		//std::cout << timeCounter << std::endl;
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


		timeElapsed = bulletClock.getElapsedTime();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeElapsed.asSeconds() > 0.5f)
		{
			bulletClock.restart();
			m_player.SpawnBullet();
		}


		sf::Vector2f playerPos = m_player.getPosition();
		m_mainView.setCenter(playerPos);
		//std::cout << playerPos.x << "," << playerPos.y << std::endl;
		m_backgroundSprite.setPosition(playerPos.x * 1.f - SCREEN_WIDTH / 2.f, playerPos.y * 1.f - SCREEN_HEIGHT / 2.f);
		m_emptyShaderSprite.setPosition(playerPos.x * 1.f - SCREEN_WIDTH / 2.f, playerPos.y * 1.f - SCREEN_HEIGHT / 2.f);
		

		shield->update();

		if (shield->collisionCheck(m_player.getSprite()) == true)
		{
			shield->setAlive(false);
			m_player.activateTheShield();
		}

	}
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw Main Game
	m_window.setView(m_mainView);
	m_window.draw(m_backgroundSprite);
	m_window.draw(m_emptyShaderSprite, &m_shader);
	m_world.render(m_window);
	m_player.render(m_window);
	shield->draw(m_window);

	// Draw MiniMap
	m_window.setView(m_miniMapView);
	m_world.render(m_window);
	m_player.render(m_window);

	m_window.display();
}
