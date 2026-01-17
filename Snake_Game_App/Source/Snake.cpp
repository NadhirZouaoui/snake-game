#include "Snake.h"
#include<iostream>

SnakeHead::SnakeHead():
	texture(sf::Texture("../ressources/mouthCLosed.png")),
	sprite(sf::Sprite(texture))
{
	sprite.setScale(sf::Vector2f(0.3, 0.3));
	sprite.setPosition(sf::Vector2f(400, 350));
	sprite.setOrigin(sprite.getLocalBounds().getCenter());
}


Snake::Snake() :
	m_speed(4),
	m_length(0),
	m_direction(RIGHT),
	m_previousDirection(RIGHT),
	m_tailIndex(0),
	m_headIndex(50),
	m_headObject()
{
	Grid::initializeGrid();
	for (size_t i = 0; i < 50; i++)
	{
		m_bodyArray[i] = sf::Vector2f(-1.f, -1.f);
	}
	m_headPosition = sf::Vector2f(6 * Grid::CELL_SIZE + Grid::CELL_SIZE / 2, 5 * Grid::CELL_SIZE + Grid::CELL_SIZE / 2);
}

void Snake::redirect(Direction newDirection) {
	switch (newDirection)
	{
	case UP:
		m_rotationDirection = (m_direction == LEFT) ? POSITIVE : NEGATIVE;
		break;
	case DOWN:
		m_rotationDirection = (m_direction == RIGHT) ? POSITIVE : NEGATIVE;
		break;
	case LEFT:
		m_rotationDirection = (m_direction == DOWN) ? POSITIVE : NEGATIVE;
		break;
	case RIGHT:
		m_rotationDirection = (m_direction == UP) ? POSITIVE : NEGATIVE;
		break;
	default:
		break;
	}
	if (newDirection != -m_direction)
		m_direction = newDirection;
}

void Snake::incrementStats() {
	this->m_speed +=0.05;
	this->m_length++;
	this->m_score = std::to_string(m_length);
	for (int i = 0; i < 8; i++)
		m_bodyArray[(m_tailIndex - 1) + MAXSIZE * (m_tailIndex == 0)] = m_bodyArray[m_tailIndex--];
	
}


bool Snake::collistionDetected() {
	int index = m_tailIndex;
	while ((index + 40) % MAXSIZE != m_headIndex)
	{
		if (abs(m_headPosition.x - m_bodyArray[index].x) < 5 && abs(m_headPosition.y - m_bodyArray[index].y) < 5 ||
			m_headPosition.x < Grid::CELL_SIZE * 1 || m_headPosition.x > Grid::CELL_SIZE * 13 ||
			m_headPosition.y < Grid::CELL_SIZE * 1 || m_headPosition.y > Grid::CELL_SIZE * 11)
			return true;
		index = (index + 1) % MAXSIZE;
	}
	return false;
}




bool Snake::ateFood(sf::Vector2f foodPosition) {
	if (abs(m_headPosition.x - foodPosition.x) < 5 && abs(m_headPosition.y - foodPosition.y) < 5)
		return true;
	return false;
}

void Snake::setMouthState(sf::Vector2f foodPosition) {
	if ((abs(m_headPosition.x - foodPosition.x) < 70 && abs(m_headPosition.y - foodPosition.y) < 70))
	{
		m_headObject.texture.loadFromFile("../ressources/mouthOpen.png");
		m_headObject.sprite.setTexture(m_headObject.texture);

	}
	else
	{
		m_headObject.texture.loadFromFile("../ressources/mouthClosed.png");
		m_headObject.sprite.setTexture(m_headObject.texture);

	}
}


void Snake::move() {
	sf::Vector2f step;
	auto rotationDegree = m_headObject.sprite.getRotation().asDegrees();
	auto targetAngleDgree = sf::degrees(270).asDegrees();
	Direction currentDirection = m_previousDirection;
	if (Grid::isValidPosition(m_headPosition))
	{
		currentDirection = m_direction;
	}
	switch (currentDirection)
	{
	case UP:
		step = { 0, -(float)m_speed };
		targetAngleDgree = sf::degrees(270).asDegrees();
		if (abs(rotationDegree - targetAngleDgree) > 0.1f)
			m_headObject.sprite.rotate(sf::degrees(10 * m_rotationDirection));
		break;
	case DOWN:
		step = { 0, (float)m_speed };
		targetAngleDgree = sf::degrees(90).asDegrees();
		if (abs(rotationDegree - targetAngleDgree) > 0.1f)
			m_headObject.sprite.rotate(sf::degrees(10 * m_rotationDirection));
		break;
	case LEFT:
		step = { -(float)m_speed, 0 };
		targetAngleDgree = sf::degrees(180).asDegrees();
		if (abs(rotationDegree - targetAngleDgree) > 0.1f)
			m_headObject.sprite.rotate(sf::degrees(10 * m_rotationDirection));
		break;
	case RIGHT:
		step = { (float)m_speed, 0 };
		if (abs(rotationDegree) > 0.1f && abs(rotationDegree - 360)  > 0.1f)
			m_headObject.sprite.rotate(sf::degrees(10 * m_rotationDirection));

		break;
	default:
		return;
	}
	m_headPosition += step;
	m_headObject.sprite.setPosition(m_headPosition);
	m_headIndex = (m_headIndex + 1) % MAXSIZE;
	m_bodyArray[m_headIndex] = m_headPosition;
	m_tailIndex = (m_tailIndex + 1) % MAXSIZE;
	m_previousDirection = currentDirection;
}