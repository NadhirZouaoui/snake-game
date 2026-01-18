#pragma once
#include<array>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include"constants.h"
#include<string>
#include<Core/core.h>

#define MAXSIZE 1000

enum Direction
{
	UP = 1,
	DOWN = -1,
	LEFT = -2,
	RIGHT = 2,
	STOP = 0
};
enum Sign
{
	POSITIVE = 1,
	NEGATIVE = -1
};


class Snake
{
public:
	bool m_isAlive;
	int m_length, m_tailIndex, m_headIndex;
	std::string m_score;
	float m_speed;
	Sign m_rotationDirection;
	Direction m_direction;
	Direction m_previousDirection;
	sf::Vector2f m_headPosition;
	Core::imageObject m_head;
	std::array<sf::Vector2f, MAXSIZE> m_bodyPositionsArray;
public:
	Snake();
	void redirect(Direction direction);
	void incrementStats();
	bool collistionDetected();
	bool ateFood(sf::Vector2f foodPosition);
	void setState(sf::Vector2f foodPosition);
	void renderBody(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void move();
};
