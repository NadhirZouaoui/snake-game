#pragma once
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Snake.h"
class Food
{
public:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Food();
	void generate(Snake snake);
};

