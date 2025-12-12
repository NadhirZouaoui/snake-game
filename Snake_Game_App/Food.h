#pragma once
#include <SFML/System/Vector2.hpp>

class Food
{
private:
	sf::Vector2i foodPosition;
public:
	void generateFood();
	Food();
};

