#include "Grid.h"


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
		if (abs(GRID[i].x - position.x) < 2.5 && abs(GRID[i].y - position.y) < 2.5)
			return true;
	}
	return false;
}