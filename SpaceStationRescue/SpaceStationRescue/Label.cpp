#include"Label.h"

//label
Label::Label(std::string s, float x = 0, float y = 0) :
	Widget()
{
	hasTexture = false; //standard label will have no texture
	m_id = "label";
	if (!m_font.loadFromFile("Assets\\Fonts\\arial.ttf"))
	{
		//error message
	}
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x, y);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(10);
}

//this is an alternative that we use for making ui icons
Label::Label(std::string s, float x, float y, std::string textureName) :
	Widget()
{

	if (!m_texture.loadFromFile(textureName))
	{
	}
	m_sprite.setTexture(m_texture); //texture
	m_sprite.setPosition(x, y);
	m_sprite.setScale(0.5, 0.5);

	hasTexture = true;
	m_id = "label";
	if (!m_font.loadFromFile("Assets\\Fonts\\arial.ttf"))
	{
		//error message
	}
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition((x + m_sprite.getGlobalBounds().width), y);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(10);



}

//draw the label to the window
void Label::draw(sf::RenderWindow &window)
{
	window.draw(m_text);
	if (hasTexture == true) //draw the texture if there is one
	{
		window.draw(m_sprite);
	}
}

//no current need to update the label
void Label::update()
{
}


//make the labels text underlined
void Label::setUnderLined()
{
	m_text.setStyle(sf::Text::Underlined);
}

//change the labels text
void Label::updateText(std::string s)
{
	m_text.setString(s);
}

//change the labels character size
void Label::changeTextSize(int size)
{
	m_text.setCharacterSize(size);
}