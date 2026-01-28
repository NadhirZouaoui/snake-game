#pragma once
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include"constants.h"
#include"core/Core.h"

struct Vector2fHash {
	std::size_t operator()(const sf::Vector2f& v) const noexcept {
		std::size_t h1 = std::hash<float>{}(v.x);
		std::size_t h2 = std::hash<float>{}(v.y);
		return h1 ^ (h2 << 1);
	}
};


class Grid
{
	public:
	static const int WIDTH = 14;
	static const int HEIGHT = 12;
	static const int CELL_SIZE = 70;
	static std::unordered_map<sf::Vector2f, Core::Object*, Vector2fHash> GRID;
	Grid() = default;
	static void initializeGrid();
	static bool isValidPosition(sf::Vector2f position);
	static sf::Vector2f generateRandomPosition();
};

