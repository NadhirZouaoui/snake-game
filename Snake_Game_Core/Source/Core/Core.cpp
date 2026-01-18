#include "Core.h"

#include <iostream>


    // class textObject Definition:
    Core::TextObject::TextObject(std::string fontUrl, std::string message, float size, sf::Vector2f position, sf::Color color) :
        m_fontObject(sf::Font(fontUrl)),
        m_textObject(sf::Text(m_fontObject))
    {
        m_textObject.setString(message);
        m_textObject.setCharacterSize(size);
        m_textObject.setPosition(position);
        m_textObject.setFillColor(color);
    }
    void Core::TextObject::setString(std::string message) {
        this->m_textObject.setString(message);
    }

    void Core::TextObject::render(sf::RenderWindow& window) {
        window.draw(m_textObject);
    }
    

    //class imageObject Definition:
    Core::imageObject::imageObject(std::string imageUrl, sf::Vector2f scale, sf::Vector2f position) :
        m_texture(sf::Texture(imageUrl)),
        m_sprite(sf::Sprite(m_texture))
    {
        m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
        m_sprite.setScale(scale);
        m_sprite.setPosition(position);
    }


    Core::imageObject::imageObject(std::string imageUrl, sf::Vector2f scale) :
        m_texture(sf::Texture(imageUrl)),
        m_sprite(sf::Sprite(m_texture))
    {
        m_sprite.setScale(scale);
    }


    void Core::imageObject::setImage(std::string imageUrl) {
        m_texture.loadFromFile(imageUrl);
        m_sprite.setTexture(m_texture);
    }
    void Core::imageObject::setSize(sf::Vector2f scale) {
        m_sprite.setScale(scale);
    }
    void Core::imageObject::setPosition(sf::Vector2f position) {
        m_sprite.setPosition(position);
    }
    void Core::imageObject::setColor(sf::Color color) {
        m_sprite.setColor(color);
    }
    void Core::imageObject::render(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }

    void Core::run() {
        sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 Window");
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                // Check if the user clicked the 'X' to close the window
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
            }
            window.clear(sf::Color::Black);
            window.display();
        }
    }
