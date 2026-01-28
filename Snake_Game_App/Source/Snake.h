#pragma once
#include<array>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include"constants.h"
#include<string>
#include<cmath>
#include<Core/core.h>

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


enum class CollisionState
{
	none,
	happened,
	near
};

struct Queue
{
	std::array<Direction, 4> buffer;
	int frontIndex = -1;
	Direction front() {
		return buffer[0];
	}
	Direction back() {
		return buffer[frontIndex];
	}
	void push(Direction dir) {
		if (frontIndex == -1)
			buffer[++frontIndex] = dir;
		else if (buffer[frontIndex] != dir)
			buffer[++frontIndex] = dir;
	}
	void pop() {
		for (int i = 0; i < frontIndex; i++)
			buffer[i] = buffer[i + 1];
		if (frontIndex > -1)
			frontIndex--;
	}

	void flush() {
		buffer.fill(STOP);
	}

};

class bodyPart : public Core::Object
{
public:
	sf::CircleShape m_shape;
public:
	bodyPart();
	void setPosition(sf::Vector2f pos);

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
	Queue m_directioQueue;
	sf::Vector2f m_headPosition;
	Core::imageObject m_head;
	bodyPart m_frontBodyPart;
	std::array<bodyPart, MAXSIZE> m_bodyPartsArray;
public:
	Snake();
	void redirect(Direction direction);
	void incrementStats();
	CollisionState collisionCheck(Core::Object* obj);
	void openMouth();
	void closeMouth();
	void die();
	void render(sf::RenderWindow& window);
private:
	void addBodyPartToGrid(bodyPart* part);
	void removeBodyPartFromGrid();
public:
	void move();
};
