#pragma once
#include<array>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#define MAXSIZE 256

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
	int m_speed, m_length, m_tailIndex, m_headIndex;
	Sign m_rotationDirection;
	Direction m_direction;
	sf::Vector2f m_headPosition;
	SnakeHead m_headObject;
	std::array<sf::Vector2f, MAXSIZE> m_bodyArray;
public:
	Snake();
	void redirect(Direction direction);
	void incrementStats();
	bool collistionDetected();
	bool ateFood(sf::Vector2f foodPosition);
	void move();
};


