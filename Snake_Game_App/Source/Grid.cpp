#include "Grid.h"
#include "Wall.h"
#include "Snake.h"
#include <random>
#include<iostream>
#include<typeinfo>

std::unordered_map<sf::Vector2f, Core::Object*, Vector2fHash> Grid::GRID;
void Grid::initializeGrid() {
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) {
			sf::Vector2f currentPos = { i * CELL_SIZE + CELL_SIZE / 2.0f, j * CELL_SIZE + CELL_SIZE / 2.0f };
			if (i == 0 || j == 0 || i == Grid::WIDTH - 1 || j == Grid::HEIGHT - 1) {
				GRID[currentPos] = new Wall(currentPos);
			}
			else {
				GRID[currentPos] = nullptr;
			}
		}
	}
}

bool Grid::isValidPosition(sf::Vector2f position){
	return GRID.contains(position);
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
	return {x * CELL_SIZE + CELL_SIZE / 2.f, y * CELL_SIZE + CELL_SIZE / 2.f };
}
