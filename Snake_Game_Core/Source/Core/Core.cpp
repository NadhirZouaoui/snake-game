#include "Core.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

namespace Core {
	void CreateWindow() {
		sf::Window window(sf::VideoMode({ 640, 480 }), "window test", sf::Style::Default);
		std::cin.get();
	}

	void PrintHelloWorld()
	{
		std::cout << "Hello World!\n";
		std::cin.get();
	}

}