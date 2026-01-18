#include "Food.h"
#include<iostream>
#include<cmath>
Food::Food() :
	m_texture("ressources/food.png"),
	m_sprite(m_texture)
{
	m_position = sf::Vector2(315.f, 245.f);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(sf::Vector2f(0.09, 0.09));
	m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
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
				float xPointsTooClose = abs(avoidedObject.m_bodyPositionsArray[index].x - randomPosition.x) < EPSILON_FOR_PIXELS;
				float yPointsTooClose = abs(avoidedObject.m_bodyPositionsArray[index].y - randomPosition.y) < EPSILON_FOR_PIXELS;

				if (xPointsTooClose && yPointsTooClose)
					isValidPosition = false;
				
				index = (index + 1) % MAXSIZE;
			}
		}
	}
	m_position = randomPosition;
	m_sprite.setPosition(m_position);
}


void Food::render(sf::RenderWindow& window) {
	window.draw(m_sprite);
}