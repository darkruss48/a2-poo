#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:
    Button(int x, int y, int width, int height, const std::string& text);

    void setPause(bool pause);
    bool getPause();
    bool isMouseOver(sf::Vector2i mousePos);
    bool isClicked(sf::Vector2i mousePos);
    void render(sf::RenderWindow& window);
    sf::RectangleShape getButtonShape();
    sf::Text getText();

private:
    sf::RectangleShape buttonShape;
    bool pause;
    sf::Text text;
};