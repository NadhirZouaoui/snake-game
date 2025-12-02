#include "Core/Core.h"


class Vector2
{
public:
	int x, y;
	bool operator==(auto& other) {
		return this.x == other.x && this.y == other.y;
	}
	Vector2(): x(0), y(0) {};
	Vector2(int x, int y) {
		this->x = x;
		this->y = y;
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
		m_direction(RIGHT),
		m_length(3),
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

};


int main()
{
	Core::CreateWindow();
	Core::PrintHelloWorld();
}