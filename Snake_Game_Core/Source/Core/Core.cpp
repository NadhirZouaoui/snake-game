#include "Core.h"
#include "../../Snake_Game_App/Snake.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

namespace Core {


	void CreateWindow() {
        sf::RenderWindow window(sf::VideoMode({ 980, 830 }), "My window");
        window.setFramerateLimit(60);
        sf::Texture backGroundtexture("../ressources/gameBackground.jpg");
        sf::Sprite backGroundsprite(backGroundtexture);
        backGroundsprite.setScale(sf::Vector2f(1.4, 1.4));
        Snake snake;
        // run the program as long as the window is open
        while (window.isOpen())
        {
            
            // check all the window's events that were triggered since the last iteration of the loop
            while (const std::optional event = window.pollEvent())
            {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                    snake.setDirection(RIGHT);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                    snake.setDirection(UP);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                    snake.setDirection(LEFT);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                    snake.setDirection(DOWN);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    snake.setDirection(STOP);
            }
            if (snake.collistionDetected())
            {
                std::cout << "collision Detected";
            }
            
            window.clear();
            window.draw(backGroundsprite);
            snake.move();
            window.draw(snake.m_headObject.sprite);
            window.display();
        }
        std::cout << snake.m_direction;
	}

	void PrintHelloWorld()
	{
		std::cout << "Hello World!\n";
		std::cin.get();
	}

}