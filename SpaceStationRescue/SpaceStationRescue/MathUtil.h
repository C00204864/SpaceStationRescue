#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <SFML/Graphics.hpp>

static bool checkCircleRectangleCollision(sf::CircleShape & circle, sf::FloatRect & rectangle)
{
	sf::Vector2f circlePos = circle.getPosition();
	float circleRad = circle.getRadius();
	float right = rectangle.left + rectangle.width;
	float closestX = circlePos.x < rectangle.left ? rectangle.left : (circlePos.x > right ? right : circlePos.x);
	float bottom = rectangle.top + rectangle.height;
	float closestY = circlePos.y < rectangle.top ? rectangle.top : (circlePos.y > bottom ? bottom : circlePos.y);
	float distanceX = circlePos.x - closestX;
	float distanceY = circlePos.y - closestY;
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (circleRad * circleRad);
}

static float getDistance(sf::Vector2f v1, sf::Vector2f v2)
{
	return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

static sf::Vector2f getFloatRectCenter(sf::FloatRect rect)
{
	return sf::Vector2f(rect.left + (rect.width / 2.f), rect.top + (rect.height / 2.f));
}

static sf::Vector2f setVecSize(sf::Vector2f vec, float size)
{
	float magnitude = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return sf::Vector2f(vec.x / magnitude * size, vec.y / magnitude * size);
}


#endif // !MATHUTIL_H