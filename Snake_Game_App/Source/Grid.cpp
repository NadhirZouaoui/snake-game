#include "Grid.h"
#include <random>
#include<iostream>

std::array<sf::Vector2f, 14 * 12> Grid::GRID;

void Grid::initializeGrid() {
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) 
			GRID[i + j * WIDTH] = sf::Vector2f(i * CELL_SIZE + CELL_SIZE / 2.0f, j * CELL_SIZE + CELL_SIZE / 2.0f);
	}
}

bool Grid::isValidPosition(sf::Vector2f position){
	for (int i = 0; i < 14 * 12; i++)
	{
		bool xPointsTooClose = abs(GRID[i].x - position.x) < EPSILON_FOR_PIXELS;
		bool yPointTooClose = abs(GRID[i].y - position.y) < EPSILON_FOR_PIXELS;
		if (xPointsTooClose && yPointTooClose)
			return true;
	}
	return false;
}

sf::Vector2f Grid::generateRandomPosition() {
	std::random_device rd;
	std::mt19937 generator(rd());
	int xFirstValidSquare = 1;
	int xLastValidSquare = 12;
	int yFirstValidSquare = 1;
	int yLastValidSquare = 10;
	std::uniform_int_distribution<> Xdistributor(xFirstValidSquare, xLastValidSquare);
	std::uniform_int_distribution<> Ydistributor(yFirstValidSquare, yLastValidSquare);
	int x = Xdistributor(generator);
	int y = Ydistributor(generator);
	return GRID[x + y * WIDTH];
}
