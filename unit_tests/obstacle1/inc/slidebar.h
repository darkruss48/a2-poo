#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class SlideBar {
public:
    SlideBar(int x, int y, int width, int height, int minValue, int maxValue, int initialValue);

    int getValue() const;
    void handleEvent(sf::RenderWindow& window, sf::Event& event);
    void render(sf::RenderWindow& window);

private:
    sf::RectangleShape barShape;
    sf::RectangleShape sliderShape;
    int minValue;
    int maxValue;
    int value;
    bool isDragging;
};