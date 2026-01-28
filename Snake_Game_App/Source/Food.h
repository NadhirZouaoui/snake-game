#pragma once
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Grid.h"
#include "Snake.h"
#include"constants.h"
class Food : public Core::imageObject{

public:
	Food();
	void generate();
};

