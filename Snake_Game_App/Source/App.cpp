#include "Core/Core.h"
#include<array>
#define MAXSIZE 256

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
	int m_speed, m_length, m_tailIndex, m_headIndex;
	Direction m_direction;
	Vector2 m_headPosition;
	std::array<Vector2, MAXSIZE> m_bodyArray;


public:
	Snake() : m_speed(1),
		m_length(3),
		m_direction(RIGHT),
		m_tailIndex(0),
		m_headIndex(2)
	{
		m_bodyArray[0] = {-2, 0};
		m_bodyArray[1] = {-1, 0};
		m_bodyArray[2] = { 0, 0 };
		m_headPosition = m_bodyArray[2];
	}
	
	void incrementStats() {
		this->m_speed++;
		this->m_length++;
	}
	
	bool collistionDetected() {
		int index = m_tailIndex;
		while(index != m_headIndex)
		{
			if (m_headPosition == m_bodyArray[index])
				return true;
			index = (index + 1) % MAXSIZE;
		}
		return false;
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
		m_headIndex = (m_headIndex + 1) % MAXSIZE;
		m_bodyArray[m_headIndex] = m_headPosition;
		m_tailIndex = (m_tailIndex + 1) % MAXSIZE;
	}
};


int main()
{
	Core::CreateWindow();
	Core::PrintHelloWorld();
}
