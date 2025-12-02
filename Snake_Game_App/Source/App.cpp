#include "Core/Core.h"


class Vector2
{
public:
	int x, y;
	bool operator==(auto& other) {
		return this.x == other.x && this.y == other.y;
	}
	Vector2() : x(0), y(0) {};
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
	std::vector<Vector2> m_bodyPosition;


public:

};


int main()
{
	Core::CreateWindow();
	Core::PrintHelloWorld();
}