#include "Game.h"

/// <summary>
/// Constructor for the game object
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1280, 720, 32 }, "Space Station Rescue" },
	m_exitGame{ false }, // When true game will exit
	m_player{ sf::Vector2f(2900,2850) },
	m_world{"Assets\\Levels\\Level.txt", 96, 96, m_player }
{
	// Views
	m_mainView = sf::View(m_window.getView().getCenter(), m_window.getView().getSize());
	m_miniMapView = sf::View(sf::Vector2f(2880, 2880), sf::Vector2f(5760, 5760));
	m_miniMapView.setViewport(sf::FloatRect(0.735f, 0.025f, 0.25f, 0.25f));
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
	m_backgroundSprite.setScale(2.8f * SCREEN_WIDTH / backgroundLocalBounds.width, 2.8f * SCREEN_HEIGHT / backgroundLocalBounds.height);

	// Shader
	m_emptyShaderSprite.setTexture(m_emptyShaderTexture);
	sf::FloatRect shaderLocalBounds = m_emptyShaderSprite.getLocalBounds();
	m_emptyShaderSprite.setScale(SCREEN_WIDTH / shaderLocalBounds.width, SCREEN_HEIGHT / shaderLocalBounds.height);

	if (!m_minimapTexture.loadFromFile("Assets\\Images\\minimap.png"))
	{
		std::cout << "Error: Could not load background texture." << std::endl;
	}
	m_minimapBackground.setTexture(m_minimapTexture);
	m_minimapBackground.setOrigin(m_minimapBackground.getGlobalBounds().width / 2, m_minimapBackground.getGlobalBounds().height / 2);
	m_minimapBackground.setPosition(m_miniMapView.getCenter());
	m_minimapBackground.scale(10, 10);


	// Powerups
	powerUps.push_back(new PowerUp(sf::Vector2f(500,500), PowerType::SPEED));
	powerUps.push_back(new PowerUp(sf::Vector2f(600, 600), PowerType::SHIELD));

	menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, *this, m_window);
	dieScreen = new DieScreen(SCREEN_WIDTH, SCREEN_HEIGHT, *this, m_window);
	winScreen = new WinScreen(SCREEN_WIDTH, SCREEN_HEIGHT, *this, m_window);
	m_state = State::MAINMENU;

	hud = new Hud(m_player);
}

/// <summary>
/// Destructor for the game object
/// </summary>
Game::~Game() {}

/// <summary>
/// Run the Game
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
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
			m_shader.setUniform("time", timeCounter);
		}
		render(); // As many as possible
	}
}

/// <summary>
/// Set the State for the Game
/// </summary>
/// <param name="state">The state that the game will be set to</param>
void Game::setGameState(State state)
{
	m_state = state;
}

/// <summary>
/// Close the game window
/// </summary>
void Game::endGame()
{
	m_window.close();
}

void Game::reset()
{
	m_world.reset("Assets\\Levels\\Level.txt");
	m_player.reset();
	for (auto & p : powerUps)
	{
		p->setAlive(true);
	}
	m_mainView.setCenter(m_player.getPosition());
}

/// <summary>
/// Process the game events
/// </summary>
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

/// <summary>
/// Update loop for the game
/// </summary>
/// <param name="t_deltaTime">deltatime</param>
void Game::update(sf::Time t_deltaTime)
{


	switch (m_state)
	{
	case MAINMENU:
		menu->update();
		break;
	case PLAY:
		
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeElapsed.asSeconds() > 0.25f)
			{
				bulletClock.restart();
				m_player.SpawnBullet();
			}

			m_world.update(t_deltaTime.asSeconds());

			sf::Vector2f playerPos = m_player.getPosition();
			m_mainView.setCenter(playerPos);
			m_backgroundSprite.setPosition(playerPos.x * 0.8f - SCREEN_WIDTH / 2.f - 180.f, playerPos.y * 0.8f - SCREEN_HEIGHT / 2.f - 180.f);
			m_emptyShaderSprite.setPosition(playerPos.x - SCREEN_WIDTH / 2.f, playerPos.y - SCREEN_HEIGHT / 2.f);

			for (auto & p : powerUps)
			{
				p->update();
				if (p->collisionCheck(m_player.getSprite()))
				{
					p->setAlive(false);

					if (p->getType() == PowerType::SHIELD)
					{
						m_player.activateShield();
					}
					else
					{
						m_player.activateSpeedBoost();
					}
				}
			}
		}
		hud->update(m_mainView.getCenter());
		if (m_player.getHealth() <= 0)
		{
			m_state = State::DIE;
		}
		if (m_world.getAliveNests() <= 0)
		{
			m_state = State::WIN;
		}
		break;
	case DIE:
		dieScreen->update();
		break;

	case WIN:
		winScreen->update(m_player);
		break;
	default:
		break;
	}

	
}

/// <summary>
/// Draw loop for the game
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);


	switch (m_state)
	{
	case MAINMENU:
		m_window.setView(m_window.getDefaultView());
		menu->draw();
		m_window.display();
		break;
	case PLAY:
		// Draw Main Game
		m_window.setView(m_mainView);
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_emptyShaderSprite, &m_shader);
		m_world.render(m_window);
		m_player.render(m_window);

		for (auto & p : powerUps)
		{
			p->draw(m_window);
		}
		hud->draw(m_window);

		// Draw Mini-Map
		m_window.setView(m_miniMapView);
		m_window.draw(m_minimapBackground);
		m_world.render(m_window);
		m_player.render(m_window);
		m_window.display();
		break;

	case DIE:
		// Draw Main Game
		m_window.setView(m_mainView);
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_emptyShaderSprite, &m_shader);
		m_world.render(m_window);
		m_player.render(m_window);

		for (auto & p : powerUps)
		{
			p->draw(m_window);
		}

		dieScreen->draw();
		m_window.display();
		break;
	case WIN:
		// Draw Main Game
		m_window.setView(m_mainView);
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_emptyShaderSprite, &m_shader);
		m_world.render(m_window);
		m_player.render(m_window);

		for (auto & p : powerUps)
		{
			p->draw(m_window);
		}

		winScreen->draw();
		m_window.display();
		break;
	default:
		break;
	}


	
}
