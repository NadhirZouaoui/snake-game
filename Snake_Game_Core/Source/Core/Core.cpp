#include "Core.h"
#include "../../Snake_Game_App/source/Food.h"
#include "../../Snake_Game_App/source/Snake.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include <iostream>

namespace Core {


	void CreateWindow() {
        sf::RenderWindow window(sf::VideoMode({ 980, 830 }), "My window");
        window.setFramerateLimit(100);
        sf::Texture backGroundtexture("../ressources/gameBackground.jpg");
        sf::Sprite backGroundsprite(backGroundtexture);
        backGroundsprite.setScale(sf::Vector2f(1.4, 1.4));

        Snake* snake = new Snake();

        Food food;

        sf::Font font("../ressources/Hexaplex.otf");
        sf::Text score(font);
        score.setString("SCORE : " + snake->m_score);
        score.setCharacterSize(60);
        score.setPosition(sf::Vector2(5.5f * 70.f, 0.f));
        score.setFillColor(sf::Color::Black);

        sf::Font fontGameOver("../ressources/blodyFont.ttf");
        sf::Text textGameOver(fontGameOver);
        textGameOver.setString("THE HERO HAVE FALLEN . . .");
        textGameOver.setCharacterSize(55);
        textGameOver.setPosition(sf::Vector2(1.f * 70.f, 175.f));
        textGameOver.setFillColor(sf::Color::Red);

        
        sf::Text instruction1(font);
        instruction1.setString("press R to restart");
        instruction1.setCharacterSize(35);
        instruction1.setPosition(sf::Vector2(1.f * 70.f, 7 * 70.f));
        instruction1.setFillColor(sf::Color::White);

        sf::Text instruction2(font);
        instruction2.setString("press ESC to quit");
        instruction2.setCharacterSize(35);
        instruction2.setPosition(sf::Vector2(1.f * 70.f, 8 * 70.f));
        instruction2.setFillColor(sf::Color::White);


        bool gameOver = false;
        // run the program as long as the window is open
        while (window.isOpen())
        {
            window.clear();
            if (gameOver){
                backGroundsprite.setColor(sf::Color(66, 66, 66));
            }
            else
                backGroundsprite.setColor(sf::Color(255, 255, 255));

            window.draw(backGroundsprite);
            window.draw(food.sprite);
            //drawing the snake's body
            int index = snake->m_tailIndex;
            while (index != snake->m_headIndex) {
                sf::CircleShape snakeBodyPart(30);
                if (gameOver)
                    snakeBodyPart.setFillColor(sf::Color(0, 0, 0));
                else
                    snakeBodyPart.setFillColor(sf::Color(3, 38, 11));
                snakeBodyPart.setOrigin(sf::Vector2f(30, 30));
                snakeBodyPart.setPosition(snake->m_bodyArray[index]);
                window.draw(snakeBodyPart);
                index = (index + 1) % MAXSIZE;
            }
            //drawing the head
            if (gameOver) {
                snake->m_headObject.sprite.setColor(sf::Color(66, 66, 66));
                window.draw(textGameOver);
                window.draw(instruction1);
                window.draw(instruction2);
            }
            window.draw(snake->m_headObject.sprite);
            //drawing the score
            window.draw(score);
            if (!snake->collistionDetected())
            {
                snake->move();

                snake->setMouthState(food.position);

                if (snake->ateFood(food.position))
                {
                    snake->incrementStats();
                    food.generate(*snake);
                    window.draw(food.sprite);
                    score.setString("SCORE : " + snake->m_score);

                }
            }
            else 
                gameOver = true;

            // check all the window's events that were triggered since the last iteration of the loop
            while (const std::optional event = window.pollEvent())
            {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                    snake->redirect(RIGHT);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                    snake->redirect(UP);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                    snake->redirect(LEFT);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                    snake->redirect(DOWN);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
                    snake->redirect(STOP);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                    delete snake;
                    snake = new Snake();
                    gameOver = false;
                }
            }
            window.display();
        }
        delete snake;
	}

	void PrintHelloWorld()
	{
		std::cout << "Hello World!\n";
		std::cin.get();
	}

}