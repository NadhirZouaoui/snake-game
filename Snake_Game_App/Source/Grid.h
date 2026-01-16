#pragma once
#include <SFML/System/Vector2.hpp>
#include <array>
class Grid
{
	public:
	static const int WIDTH = 14;
	static const int HEIGHT = 12;
	static const int CELL_SIZE = 70;
	static std::array<sf::Vector2f, 14 * 12> GRID;
	Grid() = default;
	static void initializeGrid();
	static bool isValidPosition(sf::Vector2f position);
};

