#include "Snake.h"
SnakeHead::SnakeHead():
	texture(sf::Texture("../ressources/mouthCLosed.png")),
	sprite(sf::Sprite(texture))
{
	sprite.setScale(sf::Vector2f(0.3, 0.3));
	sprite.setPosition(sf::Vector2f(400, 350));
	sprite.setOrigin(sprite.getLocalBounds().getCenter());
}


Snake::Snake() :
	m_speed(3),
	m_length(3),
	m_direction(RIGHT),
	m_tailIndex(0),
	m_headIndex(2),
	m_headObject()
{
	m_bodyArray[0] = { -2, 0 };
	m_bodyArray[1] = { -1, 0 };
	m_bodyArray[2] = { 400, 350 };
	m_headPosition = m_bodyArray[2];
}

void Snake::setDirection(Direction newDirection) {
	if (newDirection != -m_direction)
		m_direction = newDirection;
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


bool Snake::ateFood(sf::Vector2f foodPosition) {
	if (m_headPosition == foodPosition)
		return true;
	return false;
}


void Snake::move() {
	sf::Vector2f step;
	switch (m_direction)
	{
	case UP:
		step = { 0, -(float)m_speed };
		m_headObject.sprite.setRotation(sf::degrees(-90));
		break;
	case DOWN:
		step = { 0, (float)m_speed };
		m_headObject.sprite.setRotation(sf::degrees(90));
		break;
	case LEFT:
		step = { -(float)m_speed, 0 };
		m_headObject.sprite.setRotation(sf::degrees(180));
		break;
	case RIGHT:
		step = { (float)m_speed, 0 };
		m_headObject.sprite.setRotation(sf::degrees(0));
		break;
	default:
		return;
	}

	m_headPosition += step;
	m_headObject.sprite.setPosition(m_headPosition);
	m_headIndex = (m_headIndex + 1) % MAXSIZE;
	m_bodyArray[m_headIndex] = m_headPosition;
	m_tailIndex = (m_tailIndex + 1) % MAXSIZE;
}