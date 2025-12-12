#pragma once
#include<array>
#include <SFML/System/Vector2.hpp>
#define MAXSIZE 256

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake
{
private:
	int m_speed, m_length, m_tailIndex, m_headIndex;
	Direction m_direction;
	sf::Vector2i m_headPosition;
	std::array<sf::Vector2i, MAXSIZE> m_bodyArray;
public:
	Snake();
	void incrementStats();
	bool collistionDetected();
	bool ateFood(sf::Vector2i foodPosition);
	void move();
};


