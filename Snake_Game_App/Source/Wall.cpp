#include "Wall.h"

Wall::Wall(sf::Vector2f position) {
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setScale({ Grid::CELL_SIZE, Grid::CELL_SIZE });
	m_shape.setOrigin(m_shape.getLocalBounds().getCenter());
	m_position = position;
}