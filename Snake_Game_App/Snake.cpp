#include "Snake.h"

Snake::Snake() : 
	m_speed(1),
	m_length(3),
	m_direction(RIGHT),
	m_tailIndex(0),
	m_headIndex(2)
{
	m_bodyArray[0] = { -2, 0 };
	m_bodyArray[1] = { -1, 0 };
	m_bodyArray[2] = { 0, 0 };
	m_headPosition = m_bodyArray[2];
}


void Snake::incrementStats() {
	this->m_speed++;
	this->m_length++;
	m_bodyArray[(m_tailIndex - 1) + MAXSIZE * (m_tailIndex == 0)] = m_bodyArray[m_tailIndex--];
}


bool Snake::collistionDetected() {
	int index = m_tailIndex;
	while (index != m_headIndex)
	{
		if (m_headPosition == m_bodyArray[index])
			return true;
		index = (index + 1) % MAXSIZE;
	}
	return false;
}


bool Snake::ateFood(sf::Vector2i foodPosition) {
	if (m_headPosition == foodPosition)
		return true;
	return false;
}


void Snake::move() {
	sf::Vector2i step;
	switch (m_direction)
	{
	case UP:
		step = { 0, 1 };
		break;
	case DOWN:
		step = { 0, -1 };
		break;
	case LEFT:
		step = { -1, 0 };
		break;
	case RIGHT:
		step = { 1, 0 };
		break;
	default:
		break;
	}
	m_headPosition += step;
	m_headIndex = (m_headIndex + 1) % MAXSIZE;
	m_bodyArray[m_headIndex] = m_headPosition;
	m_tailIndex = (m_tailIndex + 1) % MAXSIZE;
}