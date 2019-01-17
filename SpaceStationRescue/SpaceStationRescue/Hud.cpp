#include "Hud.h"

Hud::Hud(Player & p):
	m_refPlayer(p)
{
	if (!m_font.loadFromFile("Assets\\Fonts\\arial.ttf"))
	{

	}
	m_health.setFont(m_font);
	m_workerAmount.setFont(m_font);
	m_health.setCharacterSize(50);
	m_workerAmount.setCharacterSize(45);

	m_health.setString("Health: " + 0);
	m_workerAmount.setString("Workers: " + 0);

}

Hud::~Hud()
{
}

void Hud::update(sf::Vector2f trackPos)
{
	m_health.setString("Health: " + std::to_string(m_refPlayer.getHealth()));
	m_workerAmount.setString("Workers: " + std::to_string(m_refPlayer.getWorkersAmount()));

	m_health.setPosition(trackPos.x - 630, trackPos.y - 350);
	m_workerAmount.setPosition(trackPos.x- 630, trackPos.y- 290);
}

void Hud::draw(sf::RenderWindow & window)
{
	window.draw(m_health);
	window.draw(m_workerAmount);
}
