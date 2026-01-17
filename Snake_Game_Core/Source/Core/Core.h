#pragma once
#include<vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include<string>

namespace Core {
    class Text
    {
    public:
        sf::Font m_fontObject;
        sf::Text m_textObject;


    public:
        Text(std::string fontUrl, std::string message, float size, sf::Vector2f position, sf::Color color);
        void setString(std::string message);

    };

	void PrintHelloWorld();
	void CreateWindow();
}