#pragma once
#include<array>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#define MAXSIZE 2000

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
class SnakeHead {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	SnakeHead();

};

class Snake
{
public:
	int m_length, m_tailIndex, m_headIndex;
	float m_speed;
	Sign m_rotationDirection;
	Direction m_direction;
	Direction m_previousDirection;
	sf::Vector2f m_headPosition;
	SnakeHead m_headObject;
	std::array<sf::Vector2f, MAXSIZE> m_bodyArray;
public:
	Snake();
	void redirect(Direction direction);
	void incrementStats();
	bool collistionDetected();
	bool ateFood(sf::Vector2f foodPosition);
	bool isValidPosition();
	void move();
};
