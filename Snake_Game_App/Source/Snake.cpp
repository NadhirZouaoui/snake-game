#include "Snake.h"
#include "Wall.h"
#include "Food.h"

#include<iostream>



bodyPart::bodyPart():
	m_shape(30)
{
	m_shape.setOrigin(m_shape.getGlobalBounds().getCenter());
	m_shape.setFillColor(sf::Color(3, 38, 11));
}
void bodyPart::setPosition(sf::Vector2f pos) {
	m_shape.setPosition(pos);
}

Snake::Snake() :
	m_isAlive(true),
	m_speed(4),
	m_length(0),
	m_direction(STOP),
	m_previousDirection(STOP),
	m_tailIndex(0),
	m_headIndex(50),
	m_head("ressources/mouthCLosed.png", sf::Vector2f(0.3, 0.3))
{
	m_headPosition = sf::Vector2f(6 * Grid::CELL_SIZE + Grid::CELL_SIZE / 2, 5 * Grid::CELL_SIZE + Grid::CELL_SIZE / 2);
	m_head.setPosition(m_headPosition);
	m_head.m_sprite.setOrigin(m_head.m_sprite.getLocalBounds().getCenter());
	m_directioQueue.flush();
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
	for (int i = 0; i < GROTH_AFTER_EATING; i++) {
		m_bodyPartsArray[(m_tailIndex - 1) + MAXSIZE * (m_tailIndex == 0)] = m_bodyPartsArray[m_tailIndex];
		m_tailIndex = (m_tailIndex - 1) + MAXSIZE * (m_tailIndex == 0);
	}
}
void Snake::openMouth() {
	m_head.m_texture.loadFromFile("ressources/mouthOpen.png");
	m_head.m_sprite.setTexture(m_head.m_texture);
}

void Snake::closeMouth() {
	m_head.m_texture.loadFromFile("ressources/mouthClosed.png");
	m_head.m_sprite.setTexture(m_head.m_texture);
}

void Snake::die() {
	m_head.m_texture.loadFromFile("ressources/dead.png");
	m_head.m_sprite.setTexture(m_head.m_texture);
}


CollisionState Snake::collisionCheck(Core::Object* obj) {
	float localGridSquareCenter = 35;
	float xHeadGridBasedPos = m_headPosition.x + localGridSquareCenter - std::fmod(m_headPosition.x, Grid::CELL_SIZE);
	float yHeadGridBasedPos = m_headPosition.y + localGridSquareCenter - std::fmod(m_headPosition.y, Grid::CELL_SIZE);
	sf::Vector2f headGridBasedPosition = sf::Vector2f(xHeadGridBasedPos, yHeadGridBasedPos);
	
	if (Grid::GRID[headGridBasedPosition] != nullptr && typeid(*Grid::GRID[headGridBasedPosition]) == typeid(*obj)) {
		return CollisionState::happened;
	}
	//detect near collision
	sf::Vector2f stepToNextGrid;
	switch (m_direction)
	{
	case UP:
		stepToNextGrid = { 0, -70.f};
		break;
	case DOWN:
		stepToNextGrid = { 0, 70.f };
		break;
	case LEFT:
		stepToNextGrid = { -70.f, 0 };
		break;
	case RIGHT:
		stepToNextGrid = { 70.f, 0 };
		break;
	default:
		stepToNextGrid = {0 , 0};
	}
	if (Grid::GRID[headGridBasedPosition + stepToNextGrid] != nullptr && typeid(*Grid::GRID[headGridBasedPosition + stepToNextGrid]) == typeid(*obj)) {
		return CollisionState::near;
	}

	return CollisionState::none;
	
	
}






void Snake::render(sf::RenderWindow& window) {
	int index = m_tailIndex;
	while (index != m_headIndex) {
		window.draw(m_bodyPartsArray[index].m_shape);
		index = (index + 1) % MAXSIZE;
	}
	m_head.render(window);
}


void Snake::addBodyPartToGrid(bodyPart* part) {
	Grid::GRID[part->m_position] = part;
}

void Snake::removeBodyPartFromGrid() {
	Grid::GRID[m_bodyPartsArray[m_tailIndex].m_position] = nullptr;
}

void Snake::move() {
	sf::Vector2f step;
	auto rotationDegree = m_head.m_sprite.getRotation().asDegrees();
	auto targetAngleDgree = sf::degrees(270).asDegrees();
	Direction currentDirection = m_previousDirection;
	if (m_previousDirection != m_direction)
		m_directioQueue.push(m_direction);
	if (Grid::isValidPosition(m_headPosition))
	{
		currentDirection = m_directioQueue.front();
		m_directioQueue.pop();
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
		m_previousDirection = STOP;
		return;
	}

	m_headPosition += step;
	float cellCenter = Grid::CELL_SIZE / 2;
	if (std::fmod(m_headPosition.x, Grid::CELL_SIZE) < cellCenter + EPSILON_FOR_PIXELS && std::fmod(m_headPosition.x, Grid::CELL_SIZE) > cellCenter - EPSILON_FOR_PIXELS &&
		std::fmod(m_headPosition.y, Grid::CELL_SIZE) < cellCenter + EPSILON_FOR_PIXELS && std::fmod(m_headPosition.y, Grid::CELL_SIZE) > cellCenter - EPSILON_FOR_PIXELS)
	{
		addBodyPartToGrid(&m_frontBodyPart);
		m_headPosition.x += cellCenter - std::fmod(m_headPosition.x, Grid::CELL_SIZE);
		m_headPosition.y += cellCenter - std::fmod(m_headPosition.y, Grid::CELL_SIZE);
		m_frontBodyPart.m_position = m_headPosition;
		m_frontBodyPart.setPosition(m_headPosition);
		
	}
	if (Grid::isValidPosition(m_bodyPartsArray[m_tailIndex].m_position)){
		removeBodyPartFromGrid();
	}
	m_head.m_sprite.setPosition(m_headPosition);
	m_bodyPartsArray[m_headIndex].m_position = m_headPosition;
	m_bodyPartsArray[m_headIndex].setPosition(m_headPosition);
	m_headIndex = (m_headIndex + 1) % MAXSIZE;
	m_tailIndex = (m_tailIndex + 1) % MAXSIZE;
	m_previousDirection = currentDirection;
}

