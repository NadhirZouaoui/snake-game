#include "Food.h"
#include<iostream>
#include<cmath>
Food::Food() :
	texture("../ressources/food.png"),
	sprite(texture)
{
	position = sf::Vector2(315.f, 245.f);
	sprite.setPosition(position);
	sprite.setScale(sf::Vector2f(0.09, 0.09));
	sprite.setOrigin(sprite.getLocalBounds().getCenter());
}

void Food::generate(Snake avoidedObject) {
	bool isValidPosition = false;
	sf::Vector2f randomPosition;
	while (!isValidPosition) {
		randomPosition = Grid::generateRandomPosition();
		int index = avoidedObject.m_tailIndex;
		isValidPosition = true;
		{
			while (index != avoidedObject.m_headIndex && isValidPosition) {
				if (abs(avoidedObject.m_bodyArray[index].x - randomPosition.x) < 5 && abs(avoidedObject.m_bodyArray[index].y - randomPosition.y) < 5)
				{
					isValidPosition = false;
				}
					index = (index + 1) % MAXSIZE;
			}
		}
	}
	position = randomPosition;
	sprite.setPosition(position);
}