#include "Core/Core.h"
class Snake
{
private:
	int speed, direction, length;
	Vector2 headPosition;
	std::vector<int> body;


public:
	
};

class Vector2
{
public:
	int x, y;
	bool operator==(auto& other) {
		return this.x == other.x && this.y == other.y;
 	}
	Vector2() : x(0), y(0){};
};


int main()
{
	Core::CreateWindow();
	Core::PrintHelloWorld();
}