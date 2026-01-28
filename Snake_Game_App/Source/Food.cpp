#include "Food.h"
#include "Snake.h"
#include<iostream>
#include<cmath>
Food::Food() :
	Core::imageObject("ressources/food.png", sf::Vector2f(0.09, 0.09), sf::Vector2(315.f, 245.f))
{
	Grid::GRID[m_position] = this;
}

void Food::generate() {
	sf::Vector2f randomPosition = Grid::generateRandomPosition();
	while (Grid::GRID[randomPosition] != nullptr) {
		randomPosition = Grid::generateRandomPosition();
	}
	Grid::GRID[m_position] = nullptr;
	m_position = randomPosition;
	m_sprite.setPosition(m_position);
	Grid::GRID[m_position] = this;
}

