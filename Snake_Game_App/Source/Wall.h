#include <SFML/System/Vector2.hpp>
#include "Grid.h"
#include"constants.h"
#include"Core/Core.h"

class Wall : public Core::Object
{
public:
	sf::RectangleShape m_shape;


public:
	Wall(sf::Vector2f position);
};

