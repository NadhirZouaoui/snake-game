#pragma once
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Snake.h"
#include"constants.h"
class Food
{
public:
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
public:
	Food();
	void generate(Snake snake);
	void render(sf::RenderWindow& window);
};

