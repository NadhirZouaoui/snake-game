#include "Core/Core.h"

class Vector2
{
public:
	int x, y;
	Vector2() : x(0), y(0) {};
	Vector2(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool operator==(const Vector2& other) {
		return x == other.x && y == other.y;
	}
	Vector2& operator += (auto& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	
};

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
	int m_speed, m_length;
	Direction m_direction;
	Vector2 m_headPosition;
	std::vector<Vector2> m_bodyPosition{2};


public:
	Snake() : m_speed(1),
		m_length(3),
		m_direction(RIGHT),
		m_headPosition({0,0})
	{}
	
	void incrementStats() {
		this->m_speed++;
		this->m_length++;
	}
	
	bool collistionDetected() {
		for (auto& bodyPartPosition : m_bodyPosition)
		{
			if (bodyPartPosition == m_headPosition)
				return true;
		}
		return true;
	}
	
	bool ateFood(Vector2 foodPosition) {
		if (m_headPosition == foodPosition)
			return true;
		return false;
	}
	void move() {
		Vector2 step;
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
		for (auto& bodyPartPosition : m_bodyPosition)
		{
			bodyPartPosition += step;
		}
	}
};


int main()
{
	Core::CreateWindow();
	Core::PrintHelloWorld();
}