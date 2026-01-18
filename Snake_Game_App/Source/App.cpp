#include "Core/Core.h"
#include "Snake.h"
#include "Food.h"
#include "Grid.h"
#include"constants.h"
#include<iostream>
class snakeGameApp : public Core
{
public:

	void run() override {
		sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "My window");
		window.setFramerateLimit(100);
		std::cout << std::filesystem::current_path() << '\n\n\n';
		sf::Vector2f backGroundImageScale = sf::Vector2f(1.4, 1.4);
		imageObject backGround("ressources/gameBackground.jpg", backGroundImageScale);
		
		Snake* snake = new Snake();
		Food food;

		TextObject score("ressources/Hexaplex.otf", "SCORE : " + snake->m_score, 60, sf::Vector2(5.5f * 70.f, 0.f), sf::Color::Black);
		TextObject gameOverMessage("ressources/blodyFont.ttf", "THE HERO HAS FALLEN . . .", 55, sf::Vector2(1 * 70.f, 175.f), sf::Color::Red);
		TextObject instruction1("ressources/Hexaplex.otf", "press R to restart", 35, sf::Vector2(1 * 70.f, 7 * 70.f), sf::Color::White);
		TextObject instruction2("ressources/Hexaplex.otf", "press ESC to quit", 35, sf::Vector2(1 * 70.f, 8 * 70.f), sf::Color::White);
	
		while (window.isOpen())
		{
			window.clear();
			backGround.render(window);
			food.render(window);
			snake->setState(food.m_position);
			snake->render(window);
			score.render(window);
			if (snake->collistionDetected()){
				snake->m_isAlive = false;
				backGround.setColor(sf::Color(66, 66, 66));
				gameOverMessage.render(window);
				instruction1.render(window);
				instruction2.render(window);
			}
			else{
				snake->move();
				if (snake->ateFood(food.m_position)){
					snake->incrementStats();
					food.generate(*snake);
					food.render(window);
					score.setString("SCORE : " + snake->m_score);
				}
				backGround.setColor(sf::Color::White);
			}

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
					snake->m_isAlive = true;
				}
			}
			window.display();
		}
		delete snake;
	}
};

int main()
{
	snakeGameApp myApp;
	myApp.run();
}
