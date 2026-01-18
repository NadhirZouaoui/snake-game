#include "Snake.h"
#include<iostream>




Snake::Snake() :
	m_isAlive(true),
	m_speed(4),
	m_length(0),
	m_direction(STOP),
	m_previousDirection(RIGHT),
	m_tailIndex(0),
	m_headIndex(50),
	m_head("ressources/mouthCLosed.png", sf::Vector2f(0.3, 0.3))
{
	Grid::initializeGrid();
	m_headPosition = sf::Vector2f(6 * Grid::CELL_SIZE + Grid::CELL_SIZE / 2, 5 * Grid::CELL_SIZE + Grid::CELL_SIZE / 2);
	m_head.setPosition(m_headPosition);
	m_head.m_sprite.setOrigin(m_head.m_sprite.getLocalBounds().getCenter());
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
	for (int i = 0; i < GROTH_AFTER_EATING; i++)
		m_bodyPositionsArray[(m_tailIndex - 1) + MAXSIZE * (m_tailIndex == 0)] = m_bodyPositionsArray[m_tailIndex--];
	
}


bool Snake::collistionDetected() {
	int index = m_tailIndex;
	while ((index + 40) % MAXSIZE != m_headIndex)
	{
		if (abs(m_headPosition.x - m_bodyPositionsArray[index].x) < EPSILON_FOR_PIXELS && abs(m_headPosition.y - m_bodyPositionsArray[index].y) < EPSILON_FOR_PIXELS ||
			m_headPosition.x < Grid::CELL_SIZE * 1 || m_headPosition.x > Grid::CELL_SIZE * 13 ||
			m_headPosition.y < Grid::CELL_SIZE * 1 || m_headPosition.y > Grid::CELL_SIZE * 11)
			return true;
		index = (index + 1) % MAXSIZE;
	}
	return false;
}




bool Snake::ateFood(sf::Vector2f foodPosition) {
	bool xPointsTooClose = abs(m_headPosition.x - foodPosition.x) < 2 * EPSILON_FOR_PIXELS;
	bool yPointsTooClose = abs(m_headPosition.y - foodPosition.y) < 2 * EPSILON_FOR_PIXELS;
	if (xPointsTooClose && yPointsTooClose)
		return true;
	return false;
}

void Snake::setState(sf::Vector2f foodPosition) {
	bool xPointsNear = abs(m_headPosition.x - foodPosition.x) < 70;
	bool yPointsNear = abs(m_headPosition.y - foodPosition.y) < 70;
	if (xPointsNear && yPointsNear)
	{
		m_head.m_texture.loadFromFile("ressources/mouthOpen.png");
		m_head.m_sprite.setTexture(m_head.m_texture);

	}
	else
	{
		m_head.m_texture.loadFromFile("ressources/mouthClosed.png");
		m_head.m_sprite.setTexture(m_head.m_texture);

	}
	if (!m_isAlive)
	{
		m_head.m_texture.loadFromFile("ressources/dead.png");
		m_head.m_sprite.setTexture(m_head.m_texture);
	}
}


void Snake::renderBody(sf::RenderWindow& window) {
	int index = m_tailIndex;
	while (index != m_headIndex) {
		sf::CircleShape snakeBodyPart(30);
		snakeBodyPart.setOrigin(sf::Vector2f(30, 30));
		snakeBodyPart.setPosition(m_bodyPositionsArray[index]);
		snakeBodyPart.setFillColor(sf::Color(3, 38, 11));
		window.draw(snakeBodyPart);
		index = (index + 1) % MAXSIZE;
	}
}

void Snake::render(sf::RenderWindow& window) {
	renderBody(window);
	m_head.render(window);
}




void Snake::move() {
	sf::Vector2f step;
	auto rotationDegree = m_head.m_sprite.getRotation().asDegrees();
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
		if (abs(rotationDegree - targetAngleDgree) > EPSILON_FOR_FPS)
			m_head.m_sprite.rotate(sf::degrees(10 * m_rotationDirection));
		break;
	case DOWN:
		step = { 0, (float)m_speed };
		targetAngleDgree = sf::degrees(90).asDegrees();
		if (abs(rotationDegree - targetAngleDgree) > EPSILON_FOR_FPS)
			m_head.m_sprite.rotate(sf::degrees(10 * m_rotationDirection));
		break;
	case LEFT:
		step = { -(float)m_speed, 0 };
		targetAngleDgree = sf::degrees(180).asDegrees();
		if (abs(rotationDegree - targetAngleDgree) > EPSILON_FOR_FPS)
			m_head.m_sprite.rotate(sf::degrees(10 * m_rotationDirection));
		break;
	case RIGHT:
		step = { (float)m_speed, 0 };
		if (abs(rotationDegree) > 0.1f && abs(rotationDegree - 360)  > EPSILON_FOR_FPS)
			m_head.m_sprite.rotate(sf::degrees(10 * m_rotationDirection));

		break;
	default:
		return;
	}

	m_headPosition += step;
	m_head.m_sprite.setPosition(m_headPosition);
	m_bodyPositionsArray[m_headIndex] = m_headPosition;
	m_headIndex = (m_headIndex + 1) % MAXSIZE;
	m_tailIndex = (m_tailIndex + 1) % MAXSIZE;
	m_previousDirection = currentDirection;
}

