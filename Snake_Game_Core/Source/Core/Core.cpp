#include "Core.h"
#include "../../Snake_Game_App/source/Food.h"
#include "../../Snake_Game_App/source/Snake.h"


#include <iostream>

namespace Core {


    Text::Text(std::string fontUrl, std::string message, float size, sf::Vector2f position, sf::Color color) :
        m_fontObject(sf::Font(fontUrl)),
        m_textObject(sf::Text(m_fontObject))
    {
        m_textObject.setString(message);
        m_textObject.setCharacterSize(size);
        m_textObject.setPosition(position);
        m_textObject.setFillColor(color);
    }
    void Text::setString(std::string message) {
        this->m_textObject.setString(message);
    }

    //-----------------------------------------------------------------------------------------------------
	void CreateWindow() {
        sf::RenderWindow window(sf::VideoMode({ 980, 830 }), "My window");
        window.setFramerateLimit(100);
        sf::Texture backGroundtexture("../ressources/gameBackground.jpg");
        sf::Sprite backGroundsprite(backGroundtexture);
        backGroundsprite.setScale(sf::Vector2f(1.4, 1.4));

        Snake* snake = new Snake();
        Food food;
        Text score("../ressources/Hexaplex.otf", "SCORE : " + snake->m_score, 60, sf::Vector2(5.5f * 70.f, 0.f), sf::Color::Black);
        Text gameOverMessage("../ressources/blodyFont.ttf", "THE HERO HAS FALLEN . . .", 55, sf::Vector2(1.f * 70.f, 175.f), sf::Color::Red);
        Text instruction1("../ressources/Hexaplex.otf", "press R to restart", 35, sf::Vector2(1.f * 70.f, 7 * 70.f), sf::Color::White);
        Text instruction2("../ressources/Hexaplex.otf", "press ESC to quit", 35, sf::Vector2(1.f * 70.f, 8 * 70.f), sf::Color::White);
        bool gameOver = false;
        // run the program as long as the window is open
        while (window.isOpen())
        {
            window.clear();
            if (gameOver){
                backGroundsprite.setColor(sf::Color(100, 100, 100));
            }
            else
                backGroundsprite.setColor(sf::Color(255, 255, 255));

            window.draw(backGroundsprite);
            window.draw(food.sprite);
            //drawing the snake's body
            int index = snake->m_tailIndex;
            while (index != snake->m_headIndex) {
                sf::CircleShape snakeBodyPart(30);
                snakeBodyPart.setFillColor(sf::Color(3, 38, 11));
                snakeBodyPart.setOrigin(sf::Vector2f(30, 30));
                snakeBodyPart.setPosition(snake->m_bodyArray[index]);
                window.draw(snakeBodyPart);
                index = (index + 1) % MAXSIZE;
            }
            //drawing the head
            if (gameOver) {
                snake->m_headObject.texture.loadFromFile("../ressources/dead.png");
                snake->m_headObject.sprite.setTexture(snake->m_headObject.texture);
                window.draw(gameOverMessage.m_textObject);
                window.draw(instruction1.m_textObject);
                window.draw(instruction2.m_textObject);
            }
            window.draw(snake->m_headObject.sprite);
            //drawing the score
            window.draw(score.m_textObject);
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