#pragma once
#include<SFML\Graphics.hpp>

class Animation {

public:
	Animation();
	Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
	void update(int row, float dt);
	bool isAnimFinished();
	void setFinished(bool isFinish);
	sf::IntRect uvRect;
	void PlayAnimationOnce(bool b);
	void reset();
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
	bool animationFinished;
	bool playOnce;

};
