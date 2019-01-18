#include "WinScreen.h"

WinScreen::WinScreen(float width, float height, Game & game, sf::RenderWindow & window):
	m_game(&game),
	m_window(window)
{
	m_itemSelected = false;
	//m_label.setUnderLined();
	m_widgets[0] = new Button("Try Again", (width / 0.60f), float(height / (MAX_ITEMS - 0.5f) * 1.0f));
	m_widgets[0]->getFocus();
	m_widgets[0]->Enter = std::bind(&WinScreen::tryAgain, this); //func bind
	m_widgets[1] = new Button("Quit", (width / 0.60f), float(height / (MAX_ITEMS - 0.5f) * 1.0f));
	m_widgets[1]->Enter = std::bind(&WinScreen::EndGame, this); //func bind
	m_background.setSize(sf::Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_background.setFillColor(sf::Color(0, 0, 0, 0));

	m_selectedItemIndex = 0; //start at top 

	m_gui.horizontal = true; //control scheme

						   //add ui elements to gui
	for (auto & var : m_widgets)
	{
		m_gui.addWidget(var);
	}




	//m_gui.addLabel(&m_label);
	transparency = 0;
	transparency2 = 0;

	if (!m_font.loadFromFile("Assets\\Fonts\\arial.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
	}

	m_text.setFont(m_font);
	m_text2.setFont(m_font);

	m_text.setCharacterSize(100);
	m_text.setString("Mission Complete!");
	m_text.setPosition(sf::Vector2f(m_window.getSize().x , m_window.getSize().y / 2.5));
	m_text.setFillColor(sf::Color(255, 255, 255, transparency));

	m_text2.setCharacterSize(50);
	m_text2.setString("Workers Saved: ");
	m_text2.setPosition(sf::Vector2f(m_window.getSize().x, m_window.getSize().y / 2.5));
	m_text2.setFillColor(sf::Color(255, 255, 255, transparency));

	m_widgets[0]->updateFocusColor(sf::Color(0, 255, 0, 255));
	m_widgets[1]->updateFocusColor(sf::Color(0, 255, 0, 255));
	m_count = 0;
}

WinScreen::~WinScreen()
{
	for (auto & var : m_widgets)
	{
		delete var;
	}
}

void WinScreen::draw()
{
	m_window.draw(m_background);
	m_gui.draw(m_window);
	m_window.draw(m_text);
	m_window.draw(m_text2);
}

void WinScreen::update(Player & player)
{
	sf::Vector2f halfScale(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

	if (transparency < 125)
	{
		transparency += 5.f;
		m_background.setFillColor(sf::Color(0, 0, 0, transparency));

	}

	if (transparency2 < 255)
	{

		transparency2 += 5.f;
		m_text.setFillColor(sf::Color(255, 255, 255, transparency2));
		m_text2.setFillColor(sf::Color(255, 255, 255, transparency2));
	}

	m_widgets[0]->updatePosition(m_window.getView().getCenter() + sf::Vector2f(-300, 200));
	m_widgets[1]->updatePosition(m_window.getView().getCenter() + sf::Vector2f(100, 200));

	m_text.setPosition(m_window.getView().getCenter() + sf::Vector2f(-400, -100));
	m_text2.setPosition(m_window.getView().getCenter() + sf::Vector2f(-400, 50));
	m_text2.setString("Workers Saved: " + std::to_string(player.getWorkersAmount()));
	m_background.setPosition(m_window.getView().getCenter() - halfScale);
	if (m_count > 60)
	{
		m_gui.update(m_selectedItemIndex, MAX_ITEMS);

	}
	else
	{
		m_count++;
	}
}

void WinScreen::EndGame()
{
	transparency = 0;
	transparency2 = 0;
	m_background.setFillColor(sf::Color(0, 0, 0, transparency));
	m_text.setFillColor(sf::Color(255, 255, 255, transparency2));
	m_text2.setFillColor(sf::Color(255, 255, 255, transparency2));
	m_game->setGameState(State::MAINMENU);
	m_count = 0;
	m_selectedItemIndex = 0;
}

void WinScreen::tryAgain()
{
	transparency = 0;
	transparency2 = 0;
	m_background.setFillColor(sf::Color(0, 0, 0, transparency));
	m_text.setFillColor(sf::Color(255,255, 255, transparency2));
	m_text2.setFillColor(sf::Color(255, 255, 255, transparency2));
	//m_game->loadLevel("");
	//m_game->setGameState(GameState::Play);
	m_count = 0;
	m_selectedItemIndex = 0;
}
