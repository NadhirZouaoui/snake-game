#pragma once
#include<vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include<string>

class Core {
public:
    class TextObject
    {
    public:
        sf::Font m_fontObject;
        sf::Text m_textObject;

    public:
		TextObject(std::string fontUrl, std::string message, float size, sf::Vector2f position, sf::Color color);
        void setString(std::string message);
		void render(sf::RenderWindow& window);
    };



	class imageObject
	{
	public:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
	public:
		imageObject(std::string imageUrl, sf::Vector2f scale, sf::Vector2f position);
		imageObject(std::string imageUrl, sf::Vector2f scale);
		void setImage(std::string imageUrl);
		void setSize(sf::Vector2f scale);
		void setPosition(sf::Vector2f position);
		void setColor(sf::Color color);
		void render(sf::RenderWindow& window);
	};


    virtual void run();
};