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

#endif // !MATHUTIL_H